
from PIL import Image
import numpy as np
import argparse
import os

def rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

def convert_image_to_rgb565(input_file, output_file, var_name=None):
    image = Image.open(input_file).convert("RGB")
    width, height = image.size
    pixels = np.array(image)

    if var_name is None:
        var_name = os.path.splitext(os.path.basename(output_file))[0]

    header_guard = var_name.upper() + "_HPP"
    lines = [
        f"#ifndef {header_guard}",
        f"#define {header_guard}",
        "",
        f"// Image: {os.path.basename(input_file)}",
        f"// Size: {width}x{height}, Format: RGB565",
        f"const uint16_t {var_name}[] PROGMEM = {{"
    ]

    rgb_data = []
    for y in range(height):
        for x in range(width):
            r, g, b = pixels[y][x]
            rgb_data.append(rgb565(r, g, b))

    for i in range(0, len(rgb_data), width):
        row = ", ".join(f"0x{val:04X}" for val in rgb_data[i:i + width])
        lines.append("    " + row + ",")

    lines.append("};")
    lines.append("")
    lines.append(f"#define {var_name.upper()}_WIDTH {width}")
    lines.append(f"#define {var_name.upper()}_HEIGHT {height}")
    lines.append("")
    lines.append(f"#endif // {header_guard}")

    with open(output_file, "w") as f:
        f.write("\n".join(lines))

    print(f"✅ Converted {input_file} -> {output_file}")
    print(f"Variable name: {var_name}")
    print(f"Dimensions: {width}x{height}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Convert image to RGB565 .hpp")
    parser.add_argument("input", help="Input image file (PNG, JPG, etc.)")
    parser.add_argument("output", help="Output .hpp file")
    parser.add_argument("--name", help="Variable name (default: output filename)")

    args = parser.parse_args()
    convert_image_to_rgb565(args.input, args.output, args.name)
