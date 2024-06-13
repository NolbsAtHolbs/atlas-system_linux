#!/usr/bin/env python3
"""Script that finds a string in heap of a running process and replaces it."""

import sys


def print_usage():
    print("Usage: read_write_heap.py pid search_string replace_string")
    sys.exit(1)


def find_and_replace(pid, search_str, replace_str):
    """Prints usage information and exits with status code 1"""
    maps_path = f"/proc/{pid}/maps"
    mem_path = f"/proc/{pid}/mem"

    try:
        with open(maps_path, 'r') as maps_file:
            heap_region = None
            for line in maps_file:
                if '[heap]' in line:
                    heap_region = line.split(' ')[0]
                    break

            if not heap_region:
                print("Heap region not found")
                return

            heap_start, heap_end = [int(x, 16) for x in heap_region.split('-')]

        with open(mem_path, 'rb+') as mem_file:
            mem_file.seek(heap_start)
            heap_data = mem_file.read(heap_end - heap_start)

            search_bytes = search_str.encode('ascii')
            replace_bytes = replace_str.encode('ascii')
            index = heap_data.find(search_bytes)

            if index == -1:
                print("Search string not found in heap")
                return

            mem_file.seek(heap_start + index)
            mem_file.write(replace_bytes + heap_data[index + len(
                            search_bytes):index + len(replace_bytes)])
            print(f"Replaced '{search_str}' with
                  '{replace_str}' at offset {index}")

    except Exception as e:
        print(f"An error occurred: {e}")


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print_usage()

    pid = sys.argv[1]
    search_string = sys.argv[2]
    replace_string = sys.argv[3]

    if not pid.isdigit():
        print_usage()

    if len(search_string) != len(replace_string):
        print("Search string and replace string must be of the same length")
        sys.exit(1)

    find_and_replace(pid, search_string, replace_string)
