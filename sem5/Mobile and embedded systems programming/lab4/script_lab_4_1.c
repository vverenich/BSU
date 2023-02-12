#define FUSE USE VERSION 30
#define _FILE OFFSET BITS 64

#include <stdbool.h>
#include <fuse.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

##define TEXT_FOR EXAMPLE_TEXT "Hello world! Student Pavel Zhukouski,1823361"
#define TEXT_FOR_README_TXT "Student Pavel Zhukouski,1823361"
#define STR FOR TEST TXT "I love cookies"
#define AMOUNT OF LINES 61

char full_system_way[256] = "";
char test_txt[AMOUNT_OF_LINES] [64];
bool foo_directory_on = true;
bool bin directory on = true;
bool baz directory_on = true;
bool bar directory on = true;

static int get attr(const char* path, struct stat* st)
{
    memset(st, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0)
    {
        st->st_mode = S_IFDIR | 0755;
    }
    else if (strcmp(path, "/bar") == 0 & bar_directory_on)
    {
        st->st_mode = S_IFDIR | 755;
    }
    else if (strcmp(path, "/foo") == 0 & foo_directory_on)
    {
        st->st_mode = S_IFDIR | 333;
    }
    else if (strcmp(path, "/baz") == 0 && baz_directory_on)
    {
        st->st_mode = S_IFDIR | 644
    }
    else if (strcmp(path, "/bar/bin") == 0 && bin directory_on)
    {
        st->st mode = S IF DIR | 700;
    }
    else if (strcmp(path, "/foo/test.txt") == 0 && foo_directory_on)
    {
        st->st_mode = S_IF REG | 707;

        st->st size = 0;
        for (int i = 0; i < AMOUNT OF LINES; i++)
        {
            st->st_size += strlen(test_txt[i]) + 1;
        }
    }
    else if (strcmp(path, "/baz/example") == 0 && baz directory on)
    {
        st->st mode = S IFREG | 211;
        st->st_size = strlen(TEXT_FOR_EXAMPLE_TXT);
    }
    else if (strcmp(path, "/bar/bin/paste") == 0 && bin directory_on)
    {
        st->st mode = S IFREG | 555;
        struct stat buffer;
        stat("/usr/bin/paste", &buffer);
        st->st_size = buffer.st_size;
    }
    else if (strcmp(path, "/bar/bin/readme.txt") == 0 && bin_directory_on)
    {
        st->st_mode = S_IF REG | 400;
        st->st_size = strlen(TEXT_FOR_README_TXT);
    }
    else
    {
        return -2;
    }

    return 0;
}
static int read_dir(const char* path, void* buffer, fuse_fill_dirt_ladder, off_t offset, struct fuse_file_info* fi)
{
    adder(buffer, ".", NULL, 0);
    adder(buffer, "..", NULL, 0);

    if (strcmp(path, "/") == 0)
    {
        adder(buffer, "bar", NULL, 0);
        adder(buffer, "foo", NULL, 0);
        adder(buffer, "baz", NULL, 0);

        if (strcmp(full_system_way, "/mnt/fuse/") != 0)
        {
            adder(buffer, full_system_way + 1, NULL, 0);
        }

        return 0;
    }
    else if (strcmp(path, "/bar") == 0 && bar_directory_on)
    {
        adder(buffer, "bin", NULL, 0);
        return 0;
    }
    else if (strcmp(path, "/foo") == 0 && foo_directory_on)
    {
        adder(buffer, "test.txt", NULL, 0);
        return 0;
    }
    else if (strcmp(path, "/baz") == 0 && baz_directory_on)
    {
        adder(buffer, "example", NULL, 0);
        return 0;
    }
    else if (strcmp(path, "/bar/bin") == 0 & bin_directory_on)
    {
        adder(buffer, "paste", NULL, 0);
        adder(buffer, "readme.txt", NULL, 0);
        return 0;
    }

    return -2;
}

static int read_file(const char* path, char* buffer, size_t size, off_t offset, struct fuse_file_info* fi)
{
    size_t length;
    char* read data;

    if (strcmp(path, "/bar/bin/paste") == 0)
    {
        struct stat touch_stat;
        stat("/usr/bin/paste", &touch_stat);
        length = touch stat.st size;
        FILE* f = fopen("/usr/bin/paste", "rb");
        unsigned char buffer[length];
        fread(buffer, length, 1, f);
        read data = buffer;
        fclose(f);
    }
    else if (strcmp(path, "/bar/bin/readme.txt") == 0)
    {
        length = strlen(TEXT_FOR_README_TXT);
        read_data = TEXT_FOR_README TXT;
    }
    else if (strcmp(path, "/foo/text.txt") == 0)
    {
        char temp[AMOUNT OF LINES * 50 + 400];
        strcpy(temp, "");
        for (int i = 0; i < AMOUNT_OF_LINES; i++)
        {
            strcat(temp, test_txt[i]);
            strcat(temp, "\n");
        }
        length = strlen(temp);
        read data = temp;
    }
    else if (strcmp(path, "/baz/example") == 0)
    {
        length = strlen(TEXT_FOR_EXAMPLE_TXT);
        read_data = TEXT_FOR_EXAMPLE_TXT;
    }
    else
    {
        return -2;
    }

    if (offset < length)
    {
        if (offset + size > length)
        {
            size = length - offset;
        }
        memcpy(buffer, read data + offset, size);
        return size;
    }

    return 0;
}

static int remove_dir(const char* path)
{
    if (strcmp(path, "/bar/bin") == 0)
    {
        bin_directory_on = false;
    }
    else if (strcmp(path, "/bar") == 0)
    {
        bin_directory_on = false;
        bar_directory_on = false;
    }
    else if (strcmp(path, "/foo") == 0)
    {
        foo_directory_on = false;
    }
    else if (strcmp(path, "/baz") == 0)
    {
        baz_directory_on = false;
    }
    else
    {
        return -2;
    }
}

static struct fuse operations operations = {
    .getattr = get_att,
    .readdir = readdir,
    .rmdir = remove_dirt,
    .read = read_file,
};

int main(int argc, char** argv)
{
    strcpy(full_system_way, argv[1]);
    char number_line[8];
    for (int i = 0; i < AMOUNT_OF_LINES; i++)
    {
        strcat(test_txt[i], STR_FOR_TEST_TXT);
    }
    return fuse_main(argc, argv, &operations, NULL);
}
