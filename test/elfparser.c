#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <elf.h>

int main(int argc, char *argv[]){
    int32_t fd = open("./elfparser", O_RDONLY|O_SYNC);
    printf("%d\n", fd);
    Elf32_Ehdr hdr;
    assert(fd != NULL);
    assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
    assert(read(fd, (void *)&hdr, sizeof(Elf32_Ehdr)) == sizeof(Elf32_Ehdr));
    printf("%s\n", hdr.e_ident);
    switch(hdr.e_ident[EI_CLASS])
	{
		case ELFCLASS32:
			printf("32-bit objects\n");
			break;

		case ELFCLASS64:
			printf("64-bit objects\n");
			break;

		default:
			printf("INVALID CLASS\n");
			break;
    }
    return 0;
}