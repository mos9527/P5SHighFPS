#pragma once
// Dependencies
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>
#include <cstdint>
#include <map>
#include <vector>
#define LOG(fmt,...) \
	{ \
		printf("[P5SHighFPS] "); \
		printf(fmt,__VA_ARGS__); \
		printf("\n"); \
	}

#define _CONCAT2(x, y) x##y
#define CONCAT2(x, y) _CONCAT(x, y)
#define INSERT_PADDING(length) \
	uint8_t CONCAT2(pad, __LINE__)[length]

#define ASSERT_OFFSETOF(type, field, offset) \
	static_assert(offsetof(type, field) == offset, "offsetof assertion failed")

#define ASSERT_SIZEOF(type, size) \
	static_assert(sizeof(type) == size, "sizeof assertion failed")

#ifdef BASE_ADDRESS
const HMODULE MODULE_HANDLE = GetModuleHandle(nullptr);

#define ASLR(address) \
	((size_t)MODULE_HANDLE + (size_t)address - (size_t)BASE_ADDRESS)
#endif

#define FUNCTION_PTR(returnType, callingConvention, function, location, ...) \
	returnType (callingConvention *function)(__VA_ARGS__) = (returnType(callingConvention*)(__VA_ARGS__))(location)

#define PROC_ADDRESS(libraryName, procName) \
	GetProcAddress(LoadLibrary(TEXT(libraryName)), procName)

#define HOOK(returnType, callingConvention, functionName, location, ...) \
	typedef returnType callingConvention _##functionName(__VA_ARGS__); \
	_##functionName* original##functionName = (_##functionName*)(location); \
	returnType callingConvention implOf##functionName(__VA_ARGS__)

#define INSTALL_HOOK(functionName) \
	{ \
		LOG("Installing hook %s 0x%llx",#functionName,original##functionName); \
		DetourTransactionBegin(); \
		DetourUpdateThread(GetCurrentThread()); \
		DetourAttach((void**)&original##functionName, implOf##functionName); \
		DetourTransactionCommit(); \
	}

#define VTABLE_HOOK(returnType, callingConvention, className, functionName, ...) \
	typedef returnType callingConvention className##functionName(className* This, __VA_ARGS__); \
	className##functionName* original##className##functionName; \
	returnType callingConvention implOf##className##functionName(className* This, __VA_ARGS__)

#define INSTALL_VTABLE_HOOK(className, object, functionName, functionIndex) \
	{ \
		void** addr = &(*(void***)object)[functionIndex]; \
		if (*addr != implOf##className##functionName) \
		{ \
			original##className##functionName = (className##functionName*)*addr; \
			DWORD oldProtect; \
			VirtualProtect(addr, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect); \
			*addr = implOf##className##functionName; \
			VirtualProtect(addr, sizeof(void*), oldProtect, &oldProtect); \
		} \
	}

#define WRITE_MEMORY(location, type, ...) \
	{ \
		const type data[] = { __VA_ARGS__ }; \
		DWORD oldProtect; \
		VirtualProtect((void*)(location), sizeof(data), PAGE_EXECUTE_READWRITE, &oldProtect); \
		memcpy((void*)(location), data, sizeof(data)); \
		VirtualProtect((void*)(location), sizeof(data), oldProtect, &oldProtect); \
	}

#define WRITE_NOP(location, count) \
	{ \
		DWORD oldProtect; \
		VirtualProtect((void*)(location), (size_t)(count), PAGE_EXECUTE_READWRITE, &oldProtect); \
		for (size_t i = 0; i < (size_t)(count); i++) \
			*((uint8_t*)(location) + i) = 0x90; \
		VirtualProtect((void*)(location), (size_t)(count), oldProtect, &oldProtect); \
	}

#define WRITE_CALL(location, function) \
    do { \
        WRITE_MEMORY((size_t)(location), uint8_t, 0x48, 0xB8); \
        WRITE_MEMORY((size_t)(location) + 2, uint64_t, (uint64_t)(function)); \
        WRITE_MEMORY((size_t)(location) + 10, uint8_t, 0xFF, 0xD0); \
    } while(0)

inline uint32_t readUnalignedU32(void* memory)
{
	uint8_t* p = (uint8_t*)memory;
	return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}

inline uint64_t readUnalignedU64(void* memory)
{
	uint8_t* p = (uint8_t*)memory;
	return (uint64_t)p[0] | ((uint64_t)p[1] << 8) | ((uint64_t)p[2] << 16) | ((uint64_t)p[3] << 24) | ((uint64_t)p[4] << 32) | ((uint64_t)p[5] << 40) | ((uint64_t)p[6] << 48) | ((uint64_t)p[7] << 56);
}
inline uint64_t readDisplacedAddress(uint64_t memory, int dispOffset, int instLength)
{	
	int32_t disp = (int32_t)readUnalignedU32((void*)(memory + dispOffset));
	return (uint64_t)memory + instLength + disp;
}
inline uint64_t readRelCall16Address(uint64_t memory)
{
	// E8 XX XX XX XX
	return readDisplacedAddress(memory, 1, 5);
}
inline uint64_t readLongMOVAddress(uint64_t memory)
{
	// 48		89		1D		XX XX XX XX
	// REX.W	MOV		OPCODE	DISPLACEMENT
	return readDisplacedAddress(memory, 3, 7);
}
inline uint64_t readLongLEAAddress(uint64_t memory) {
	return readDisplacedAddress(memory, 3, 7);
}

inline std::map<uint64_t, std::vector<uint8_t>> origMem;
inline void writeRelCall(uint64_t address, uint64_t function) {
	int disp = function - (address + 5);
	LOG("WRTIE ADDR 0x%llx FUNC 0x%llx DISP %d", address, function, disp);
	WRITE_MEMORY(address, uint8_t, 0xE8);
	WRITE_MEMORY((size_t)address + 1, int, disp);
}

inline void restoreRelCallWrites(uint64_t address) {	
	if (origMem.count(address)) {
		auto og = origMem[address].data();
		DWORD oldProtect;
		VirtualProtect((void*)(address), 5, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy((void*)(address), og, 5);
		VirtualProtect((void*)(address),5, oldProtect, &oldProtect);
		LOG("RESTORE ADDR 0x%llx", address);
	}
	else {
		auto& ogVec = origMem[address];
		uint8_t og[5];
		memcpy(og, (void*)address, 5);
		ogVec.insert(ogVec.end(), og, og + 5);
		LOG("BACKUP ADDR @0x%llx -> 0x%llx", address, ogVec.data());
	}
}