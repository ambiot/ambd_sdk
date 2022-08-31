#include <string.h>		// memset()
#include <psram_reserve.h>
#include <ameba_soc.h>

void *Psram_reserve_realloc_for_opus(void *mem, size_t newLength)
{
	int *_mem = (int *)mem;

	if (!_mem) {
		return Psram_reserve_malloc(newLength);
	}

	else {
		int originalLength = *(_mem - 1) - 4;
		if (newLength <= originalLength) {
			void *ptrNew = Psram_reserve_malloc(newLength);
			if (ptrNew) {
				memcpy(ptrNew, _mem, newLength);
				free(_mem);
			}
			return ptrNew;
		}

		else {
			void *ptrNew = Psram_reserve_malloc(newLength);
			if (ptrNew) {
				memcpy(ptrNew, _mem, originalLength);
				free(_mem);
			}
			return ptrNew;
		}
	}
}
