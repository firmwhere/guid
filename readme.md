## guid

```shell
guid - generate guid for uefi development. @efikarl@yeah.net

options:
    -g, --guid <guid>      generate guid from <guid>
    -u, --uefi <memmap>    generate guid from uefi <memmap>
    -i, --ipmi <memmap>    generate guid from ipmi <memmap>

flags:
    -h, --help             output help info
        --uppercase        output uppercase result, or lowercase
    -s, --standard         output guid standard text result only
```

### build

```shell
# macos
$ clang guid.c -oguid

# linux
$ clang guid.c -oguid -luuid
# or
$ gcc   guid.c -oguid -luuid
```

### examples

```sh
$ ./guid

[guid.std.text] cd8f2d32-ffbd-754e-9e99-df55586420a3
  [uefi.memmap] 322d8fcd-bdff-4e75-9e99-df55586420a3
  [ipmi.memmap] df555864-20a3-9e99-4e75-bdff322d8fcd

[uefi.guid.struct]
{ 0xcd8f2d32, 0xffbd, 0x754e, { 0x9e, 0x99, 0xdf, 0x55, 0x58, 0x64, 0x20, 0xa3 } }

[uefi.guid.define]
#define GUID \
  { \
    0xcd8f2d32, 0xffbd, 0x754e, { 0x9e, 0x99, 0xdf, 0x55, 0x58, 0x64, 0x20, 0xa3 } \
  }
extern EFI_GUID gGuid;

$ ./guid --uppercase

[guid.std.text] 399C0535-FBE3-B84B-BF51-A693A5E30A2E
  [uefi.memmap] 35059C39-E3FB-4BB8-BF51-A693A5E30A2E
  [ipmi.memmap] A693A5E3-0A2E-BF51-4BB8-E3FB35059C39

[uefi.guid.struct]
{ 0x399C0535, 0xFBE3, 0xB84B, { 0xBF, 0x51, 0xA6, 0x93, 0xA5, 0xE3, 0x0A, 0x2E } }

[uefi.guid.define]
#define GUID \
  { \
    0x399C0535, 0xFBE3, 0xB84B, { 0xBF, 0x51, 0xA6, 0x93, 0xA5, 0xE3, 0x0A, 0x2E } \
  }
extern EFI_GUID gGuid;
```

```sh
./guid --uefi 00112233-4455-6677-8899-aabbccddeeff --standard --uppercase
33221100-5544-7766-8899-AABBCCDDEEFF
./guid -g 33221100-5544-7766-8899-AABBCCDDEEFF

[guid.std.text] 33221100-5544-7766-8899-aabbccddeeff
  [uefi.memmap] 00112233-4455-6677-8899-aabbccddeeff
  [ipmi.memmap] aabbccdd-eeff-8899-6677-445500112233

[uefi.guid.struct]
{ 0x33221100, 0x5544, 0x7766, { 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff } }

[uefi.guid.define]
#define GUID \
  { \
    0x33221100, 0x5544, 0x7766, { 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff } \
  }
extern EFI_GUID gGuid;

$ ./guid --ipmi aabbccdd-eeff-8899-6677-445500112233 --standard
33221100-5544-7766-8899-aabbccddeeff
$ ./guid --uefi 00112233-4455-6677-8899-aabbccddeeff --standard
33221100-5544-7766-8899-aabbccddeeff
```