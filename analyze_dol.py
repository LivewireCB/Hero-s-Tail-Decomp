import struct

def read_dol(filepath):
    with open(filepath, 'rb') as f:
        # DOL header structure
        data = f.read(256)
        
        # Parse text section offsets (0x00-0x1c) and sizes (0x20-0x3c)
        text_offsets = struct.unpack('>7I', data[0x00:0x1c])
        text_sizes = struct.unpack('>7I', data[0x20:0x3c])
        
        # Parse data section offsets (0x1c-0x28) and sizes (0x3c-0x48)
        data_offsets = struct.unpack('>11I', data[0x1c:0x48])
        data_sizes = struct.unpack('>11I', data[0x3c:0x68])
        
        # Parse text addresses (0x48-0x64) and data addresses (0x64-0xA0)
        text_addr = struct.unpack('>7I', data[0x48:0x64])
        data_addr = struct.unpack('>11I', data[0x64:0x90])
        
        # Parse bss info
        bss_addr, bss_size = struct.unpack('>II', data[0x90:0x98])
        
        # Entry point
        entry = struct.unpack('>I', data[0x98:0x9c])[0]
        
        print("Data sections:")
        for i, (off, size, addr) in enumerate(zip(data_offsets, data_sizes, data_addr)):
            if size > 0:
                print(f"  [{i}] Off: 0x{off:08x}, Size: 0x{size:08x}, Addr: 0x{addr:08x} - 0x{addr+size:08x}")
        
        print(f"\nBSS: Addr: 0x{bss_addr:08x}, Size: 0x{bss_size:08x}")
        
        # Now find which section contains 0x803B4080
        target = 0x803B4080
        print(f"\nLooking for address 0x{target:08x}:")
        
        for i, (off, size, addr) in enumerate(zip(data_offsets, data_sizes, data_addr)):
            if size > 0 and addr <= target < addr + size:
                file_offset = off + (target - addr)
                print(f"  Found in data section [{i}]")
                print(f"  File offset: 0x{file_offset:08x}")
                # Read some bytes at that location
                f.seek(file_offset)
                data_bytes = f.read(16)
                print(f"  Bytes (16): {' '.join(f'{b:02x}' for b in data_bytes)}")
                print(f"  Addresses:")
                for j in range(4):
                    val = struct.unpack('>I', data_bytes[j*4:(j+1)*4])[0]
                    print(f"    0x{target + j*4:08x}: 0x{val:08x}")

read_dol('orig/G5SE7D/sys/main.dol')
