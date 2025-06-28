import argparse
from PIL import Image
import numpy as np
import os

def save_rgb565(img, array_name, output):
    data = np.array(img.convert("RGB"))
    def to_rgb565(r, g, b):
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
    rgb565_data = [to_rgb565(r, g, b) for row in data for r, g, b in row]
    with open(output, 'w') as f:
        f.write(f"#pragma once\n#include <stdint.h>\n")
        f.write(f"#define {array_name.upper()}_WIDTH {img.width}\n")
        f.write(f"#define {array_name.upper()}_HEIGHT {img.height}\n")
        f.write(f"const uint16_t {array_name}[] = {{\n")
        for i in range(0, len(rgb565_data), 12):
            chunk = ', '.join(f"0x{val:04X}" for val in rgb565_data[i:i+12])
            f.write(f"  {chunk},\n")
        f.write("};\n")

def save_rgb888(img, array_name, output):
    data = np.array(img.convert("RGB"))
    with open(output, 'w') as f:
        f.write(f"#pragma once\n#include <stdint.h>\n")
        f.write(f"#define {array_name.upper()}_WIDTH {img.width}\n")
        f.write(f"#define {array_name.upper()}_HEIGHT {img.height}\n")
        f.write(f"const uint8_t {array_name}[] = {{\n")
        flat = data.reshape(-1, 3)
        for i in range(0, len(flat), 6):
            chunk = ', '.join(f"0x{r:02X}, 0x{g:02X}, 0x{b:02X}" for r, g, b in flat[i:i+6])
            f.write(f"  {chunk},\n")
        f.write("};\n")

def save_binary_png(img_path, array_name, output):
    with open(img_path, 'rb') as f:
        raw = f.read()
    with open(output, 'w') as f:
        f.write(f"#pragma once\n#include <stdint.h>\n")
        f.write(f"extern const uint8_t {array_name}[];\n")
        f.write(f"extern const size_t {array_name}_len;\n")
    cpp_path = output.replace('.hpp', '.cpp')
    with open(cpp_path, 'w') as f:
        f.write(f"#include <stdint.h>\n")
        f.write(f"const uint8_t {array_name}[] = {{\n")
        for i in range(0, len(raw), 12):
            chunk = ', '.join(f"0x{b:02X}" for b in raw[i:i+12])
            f.write(f"  {chunk},\n")
        f.write("};\n")
        f.write(f"const size_t {array_name}_len = sizeof({array_name});\n")

def main():
    parser = argparse.ArgumentParser(description="Convert images to C-style .hpp headers")
    parser.add_argument("image", help="Input image file (png, jpg, etc)")
    parser.add_argument("-o", "--output", help="Output .hpp file", required=True)
    parser.add_argument("-n", "--name", help="Array base name", required=True)
    parser.add_argument("-e", "--encoding", choices=["rgb565", "rgb888", "binary"], default="rgb565",
                        help="Buffer encoding format")
    parser.add_argument("--width", type=int, help="Resize width (optional)")
    parser.add_argument("--height", type=int, help="Resize height (optional)")

    args = parser.parse_args()
    img = Image.open(args.image)
    if args.width and args.height:
        img = img.resize((args.width, args.height))

    if args.encoding == "rgb565":
        save_rgb565(img, args.name, args.output)
    elif args.encoding == "rgb888":
        save_rgb888(img, args.name, args.output)
    elif args.encoding == "binary":
        save_binary_png(args.image, args.name, args.output)
    print(f"Exported {args.encoding} image to {args.output}")

if __name__ == "__main__":
    main()
