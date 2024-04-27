# MIT License
# 
# Copyright (c) 2018 Lin Min
# Modified by Rafał 'grasmanek94' Grasman - Copyright 2024
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import sys
import shutil
import tempfile
import argparse
import subprocess

parser = argparse.ArgumentParser(description="make dll wrapper")
parser.add_argument("--dumpbin", type=str, default="dumpbin.exe",
                    help="The path to dumpbin.exe provided by visual studio")
parser.add_argument("dll", type=str, help="The path to the dll file to wrap")
args = parser.parse_args()

def extract_symbols(dll):
  output = subprocess.check_output([
      args.dumpbin, "/EXPORTS", dll
  ])
  output = output.decode("utf-8")
  lines = output.split("\r\n")
  start, end = None, None
  start = next(idx for idx, line in enumerate(lines)
               if all(map(lambda entry: (entry in line),
                          ["ordinal", "hint", "RVA", "name"]))) + 2
  lines = lines[start:]
  end = next(idx for idx, line in enumerate(lines) if line == "")
  lines = lines[:end]
  if len(lines) == 0:
    raise RuntimeError(f"No exported symbols for {dll}")
  ordinal_name_pairs = []
  for line in lines:
    if "(forwarded" in line:
      ordinal, hint, name, *others = line.split()
    elif "[NONAME]" in line:
      ordinal, RVA, name, *others = line.split()
    else:
      ordinal, hint, RVA, name, *others = line.split()
    ordinal_name_pairs.append((ordinal, name))
  return ordinal_name_pairs

def write_file(filename, content):
    with open(filename, "w") as f:
      f.write(content)

if __name__ == "__main__":
  if shutil.which(args.dumpbin) is None:
    raise RuntimeError("dumpbin.exe not found in PATH, "
                       "maybe specify its path through the --dumpbin argument?")
  if not os.path.isfile(args.dll):
    raise RuntimeError(f"{args.dll} is not a valid file")

  dll_name = args.dll[:-4]
  ordinal_name_pairs = extract_symbols(args.dll)
  ordinals = [ordinal for ordinal, _ in ordinal_name_pairs]
  names = [name for _, name in ordinal_name_pairs]
  ordinal_and_names = list(zip(ordinals, names))

  # write files
  def_content = f"LIBRARY\n"
  def_content += f"EXPORTS\n"
  for ordinal, symbol in ordinal_and_names:
    #if name == '[NONAME]':
    #  def_content += f"  ExportByOrdinal{ ordinal } @{ ordinal } NONAME\n"
    #else:
    def_content += f"  { symbol } @{ ordinal }\n"
  write_file(f"{dll_name}.def", def_content)
