//
// Created by CHR on 2021/10/28.
//

#include "agorammap.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

#define FILE_PATH "/storage/emulated/0/test.txt"
#define PAGE_SIZE 4096

std::string sdcard_path = "";

bool setSdcardPath(std::string path) {
    sdcard_path = path;
    return true;
}

int test_mmap() {
//    creat("test.txt", O_RDWR);

    FILE *fp = fopen(FILE_PATH, "wb");

    std::string logPath = sdcard_path + "/test.txt";

    int fd = open(logPath.c_str(), O_RDWR | O_CREAT, 0077);
//    int fd = fileno(fp);

    LOGD("fd=%d", fd)
    //创建映射区
    char *mem = static_cast<char *>(mmap(nullptr, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (mem == MAP_FAILED) {
        perror("mmap err");

        LOGD("Error %d: Failed to open file\n", errno)

        if (errno == EEXIST) {
            LOGD("EEXIST 参数pathname 所指的文件已存在, 却使用了O_CREAT 和O_EXCL 旗标. \r\n")

        } else if (errno == EACCES) {
            LOGD("EACCESS 参数pathname 所指的文件不符合所要求测试的权限.\r\n")

        } else if (errno == EROFS) {
            LOGD("EROFS 欲测试写入权限的文件存在于只读文件系统内.\r\n")
        }
        return -1;
    }
    //拷贝数据
    memcpy(mem, "hello", 5);
    //释放
    munmap(mem, PAGE_SIZE);
    close(fd);
    LOGD("mmap success")
    return 0;
}