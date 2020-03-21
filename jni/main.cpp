#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/mman.h>

#include "alog.h"
#include "DexUtil.h"
#include "Types.h"
#include "descriptors_names.h"

int main() {
	
	const char* path = "/data/local/tmp/test.dex";
	
	int fd = open(path, O_RDONLY);
	if (!fd) {
        ALOGE("[-] create file %s failed, %s\n", path, strerror(errno));
        return -1;
    }
	
	struct stat statbuf;
	stat(path, &statbuf);
	int size = statbuf.st_size;
	ALOGI("[*] file size = %x\n", size);
	
	u1* dexbuf = (u1*) mmap(NULL, size, PROT_READ | PROT_WRITE , MAP_PRIVATE, fd, 0);
	if(dexbuf == MAP_FAILED) {
		ALOGE("[-] mmap file %s failed, %s\n", path, strerror(errno));
		return -1;
	}
	
	ALOGI("[*] mmmap dexbuf %p\n", dexbuf);
	
	DexUtil* dexUtil = new DexUtil((u1*) dexbuf);
	
	char* package;
	
	const DexClassDef* classDef0 = (DexClassDef *) dexUtil->dexGetClassDef(0);
	const char* declaring_class0 = dexUtil->dexStringByTypeIdx(classDef0->classIdx);
	ALOGI("[*] declaring_class0 = %s\n", declaring_class0);
	ALOGI("[*] declaring_class0 = %s\n", DescriptorToDot(declaring_class0).c_str());
	ALOGI("[*] declaring_class0 = %s\n", DescriptorToName(declaring_class0).c_str());
	
	const DexClassDef* classDef1 = (DexClassDef *) dexUtil->dexGetClassDef(1);
	const char* declaring_class1 = dexUtil->dexStringByTypeIdx(classDef1->classIdx);
	ALOGI("[*] declaring_class1 = %s\n", declaring_class1);
	ALOGI("[*] declaring_class1 = %s\n",DescriptorToDot(declaring_class1).c_str());
	ALOGI("[*] declaring_class1 = %s\n",DescriptorToName(declaring_class1).c_str());
	
	const DexClassDef* classDef2 = (DexClassDef *) dexUtil->dexGetClassDef(2);
	const char* declaring_class2 = dexUtil->dexStringByTypeIdx(classDef2->classIdx);
	ALOGI("[*] declaring_class2 = %s\n", declaring_class2);
	ALOGI("[*] declaring_class2 = %s\n",DescriptorToDot(declaring_class2).c_str());
	ALOGI("[*] declaring_class2 = %s\n",DescriptorToName(declaring_class2).c_str());
	
	
	delete dexUtil;
	dexUtil = NULL;
	
	munmap(dexbuf, size);
	close(fd);
	
	return 0;
}