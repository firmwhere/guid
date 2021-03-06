/*++ @file

  Copyright ©2021 Liu Yi, efikarl@yeah.net

  This program is just made available under the terms and conditions of the
  MIT license: http://www.efikarl.com/mit-license.html

  THE PROGRAM IS DISTRIBUTED UNDER THE MIT LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
--*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>
#include <uuid/uuid.h>

#ifdef __GNUC__
#include <stdint.h>
#endif

#define UEFI_GUID_STD_TXT_SIZE 0x25
#define UEFI_GUID_STR_MAX_SIZE 0x85

bool is_guid_stdtxt_format(char *guid) {
    char guid_stdtxt[] = "00112233-4455-6677-8899-AABBCCDDEEFF";

    for (int i = 0; guid[i] != '\0'; i++) {
        if (i >= sizeof(guid_stdtxt) - 1) {
            return false;
        }
        if (!isxdigit(guid[i]) && (guid[i] != guid_stdtxt[i])) {
            return false;
        }
    }
    return true;
}

void guid_hex_to_case(char *string, bool upper_or_lower) {
    if (string == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
        return;
    }

    for (int i = 0; string[i] != '\0'; i++) {
        if (upper_or_lower) {
            if (string[i] >= 'a' && string[i] <= 'f') {
                string[i] = toupper(string[i]);
            }
        } else {
            if (string[i] >= 'A' && string[i] <= 'F') {
                string[i] = tolower(string[i]);
            }
        }
    }
}

char *guid_stdtxt_to_uefi_memmap(char *stdtxt) {
    if (stdtxt == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
    }
    if (!is_guid_stdtxt_format(stdtxt)) {
        printf("ERR: invalid guid format: %s\n", stdtxt);
        return NULL;
    }
    char *memmap = stdtxt;
    sprintf(memmap,
        "%c%c%c%c%c%c%c%c-%c%c%c%c-%c%c%c%c-%c%c%c%c-%c%c%c%c%c%c%c%c%c%c%c%c",
        memmap[ 6], memmap[ 7], memmap[ 4], memmap[ 5], memmap[ 2], memmap[ 3], memmap[ 0], memmap[ 1],
        memmap[11], memmap[12], memmap[ 9], memmap[10],
        memmap[16], memmap[17], memmap[14], memmap[15],
        memmap[19], memmap[20], memmap[21], memmap[22],
        memmap[24], memmap[25], memmap[26], memmap[27], memmap[28], memmap[29], memmap[30], memmap[31], memmap[32], memmap[33], memmap[34], memmap[35]
    );
    return memmap;
}

char *ipmi_memmap_to_uefi_memmap(char *memmap) {
    if (memmap == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
    }
    if (!is_guid_stdtxt_format(memmap)) {
        printf("ERR: invalid guid format: %s\n", memmap);
        return NULL;
    }
    sprintf(memmap,
        "%c%c%c%c%c%c%c%c-%c%c%c%c-%c%c%c%c-%c%c%c%c-%c%c%c%c%c%c%c%c%c%c%c%c",
        memmap[28], memmap[29], memmap[30], memmap[31], memmap[32], memmap[33], memmap[34], memmap[35],
        memmap[24], memmap[25], memmap[26], memmap[27],
        memmap[19], memmap[20], memmap[21], memmap[22],
        memmap[14], memmap[15], memmap[16], memmap[17],
        memmap[ 0], memmap[ 1], memmap[ 2], memmap[ 3], memmap[ 4], memmap[ 5], memmap[ 6], memmap[ 7], memmap[ 9], memmap[ 10], memmap[11], memmap[12]
    );
    return memmap;
}

void uefi_guid_stdtxt_unparse(const uuid_t uuid, char *string, bool upper_or_lower)
{
    if (string == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
        return;
    }

    sprintf(string,
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        uuid[3], uuid[2], uuid[1], uuid[0],
        uuid[5], uuid[4],
        uuid[7], uuid[6],
        uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
    );
    guid_hex_to_case(string, upper_or_lower);
}

void uefi_guid_memmap_unparse(const uuid_t uuid, char *string, bool upper_or_lower)
{
    if (string == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
        return;
    }

    sprintf(string,
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        uuid[0], uuid[1], uuid[2], uuid[3],
        uuid[4], uuid[5],
        uuid[6], uuid[7],
        uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
    );
    guid_hex_to_case(string, upper_or_lower);
}

void ipmi_uuid_memmap_unparse(const uuid_t uuid, char *string, bool upper_or_lower)
{
    if (string == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
        return;
    }

    sprintf(string,
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15],
        uuid[8], uuid[9],
        uuid[6], uuid[7],
        uuid[4], uuid[5],
        uuid[0], uuid[1], uuid[2], uuid[3]
    );
    guid_hex_to_case(string, upper_or_lower);
}

void uefi_guid_member_unparse(const uuid_t uuid, char *string, bool upper_or_lower)
{
    if (string == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
        return;
    }

    sprintf(string,
        "0x%02x%02x%02x%02x, 0x%02x%02x, 0x%02x%02x, { 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x }",
        uuid[3], uuid[2], uuid[1], uuid[0],
        uuid[5], uuid[4],
        uuid[7], uuid[6],
        uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
    );
    guid_hex_to_case(string, upper_or_lower);
}

void uefi_guid_struct_unparse(const uuid_t uuid, char *string, bool upper_or_lower)
{
    char string_member[] = "0x00112233, 0x4455, 0x6677, { 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF }";

    if (string == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
        return;
    }

    uefi_guid_member_unparse(uuid, string_member, upper_or_lower);

    sprintf(string, "{ %s }", string_member);
}

void uefi_guid_define_unparse(const uuid_t uuid, char *string, bool upper_or_lower)
{
    char string_member[] = "0x00112233, 0x4455, 0x6677, { 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF }";

    if (string == NULL) {
        printf("ERR: invalid arguments in %s\n", __func__);
        return;
    }

    uefi_guid_member_unparse(uuid, string_member, upper_or_lower);

    sprintf(string,
        "#define GUID \\\n"
        "  { \\\n"
        "    %s \\\n"
        "  }\n"
        "extern EFI_GUID gGuid;"
    , string_member);
}

typedef struct {
    bool                flag;
    union {
        uint64_t        number;
        char           *string;
    }                   value;
} argument_t;

typedef struct {
    argument_t          guid;
    bool                uefi;
    bool                ipmi;
    bool                uppercase;
    bool                standard;
} arguments_t;

void help()
{
    printf(
        "\n"
        "guid - generate guid for uefi development. @efikarl@yeah.net\n"
        "\n"
        "options:\n"
        "    -g, --guid <guid>      generate guid from <guid>\n"
        "    -u, --uefi <memmap>    generate guid from uefi <memmap>\n"
        "    -i, --ipmi <memmap>    generate guid from ipmi <memmap>\n"
        "\n"
        "flags:\n"
        "    -h, --help             output help info\n"
        "        --uppercase        output uppercase result, or lowercase\n"
        "    -s, --standard         output guid standard text result only\n"
        "\n"
        );
}

typedef struct {
  uint64_t  data1;
  uint16_t  data2;
  uint16_t  data3;
  uint8_t   data4[8];
} efi_guid_t;

int arguments_init(int argc, char **argv, arguments_t *options)
{
    int                 opt;
    int                 option_index = 0;
    struct option       long_options[] = {
        { "guid"      , 1, 0, 'g' },
        { "uefi"      , 1, 0, 'u' },
        { "ipmi"      , 1, 0, 'i' },
        { "help"      , 0, 0, 'h' },
        { "uppercase" , 0, 0, '0' },
        { "standard"  , 0, 0, 's' },
        { 0           , 0, 0,  0  }
    };

    while((opt = getopt_long(argc, argv, "g:u:i:hs",long_options, &option_index))!=EOF ) {
        switch (opt) {
        case 'g':
            options->guid.value.string  = guid_stdtxt_to_uefi_memmap(optarg);
            if (!options->guid.value.string) {
                return false;
            }
            options->guid.flag          = true;
            break;
        case 'u':
            options->guid.value.string  = optarg;
            if (!is_guid_stdtxt_format(optarg)) {
                printf("ERR: invalid guid format: %s\n", optarg);
                return false;
            }
            options->uefi               = true;
            options->guid.flag          = true;
            break;
        case 'i':
            options->guid.value.string  = ipmi_memmap_to_uefi_memmap(optarg);
            if (!options->guid.value.string) {
                return false;
            }
            options->ipmi               = true;
            options->guid.flag          = true;
            break;
        case '0':
            options->uppercase = true;
            break;
        case 's':
            options->standard  = true;
            break;
        default:
            return false;
        }
    }
    return true;
}

typedef struct {
    char guid_stdtxt[UEFI_GUID_STD_TXT_SIZE];
    char uefi_memmap[UEFI_GUID_STD_TXT_SIZE];
    char ipmi_memmap[UEFI_GUID_STD_TXT_SIZE];
    char uefi_guid_struct_string[UEFI_GUID_STR_MAX_SIZE];
    char uefi_guid_define_string[UEFI_GUID_STR_MAX_SIZE];
} guids_t;

void guid_result_output_handler(
    const uuid_t        uuid,
    const arguments_t   options
    )
{
    guids_t guids = { 0 };
    uefi_guid_stdtxt_unparse(uuid, guids.guid_stdtxt, options.uppercase);
    if (options.standard) {
        printf("%s\n", guids.guid_stdtxt);
        return;
    };
    uefi_guid_memmap_unparse(uuid, guids.uefi_memmap, options.uppercase);
    ipmi_uuid_memmap_unparse(uuid, guids.ipmi_memmap, options.uppercase);
    uefi_guid_struct_unparse(uuid, guids.uefi_guid_struct_string, options.uppercase);
    uefi_guid_define_unparse(uuid, guids.uefi_guid_define_string, options.uppercase);
    printf(
        "\n"
        "[guid.std.text] %s\n"
        "  [uefi.memmap] %s\n"
        "  [ipmi.memmap] %s\n"
        "\n"
        "[uefi.guid.struct]\n"
        "%s\n"
        "\n"
        "[uefi.guid.define]\n"
        "%s\n"
        "\n",
        guids.guid_stdtxt, guids.uefi_memmap, guids.ipmi_memmap, guids.uefi_guid_struct_string, guids.uefi_guid_define_string
    );
}

int main(int argc, char **argv)
{
    arguments_t     options = { .uppercase = 0 };
    if (!arguments_init(argc, argv, &options)) {
        help();
        return 1;
    }

    uuid_t          uuid    = { 0 };
    if (options.guid.flag) {
        uuid_parse(options.guid.value.string, uuid);
    } else {
        uuid_generate(uuid);
    }

    guid_result_output_handler(uuid, options);
    return 0;
}
