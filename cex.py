#!python3
import subprocess
from pathlib import Path
import argparse
from typing import Callable
import re

def process_line(line):
    # If the line starts with a number (optionally with spaces) followed by a vertical bar,
    # then leave the line unchanged.
    if re.match(r'^\s*\d+\s*\|', line):
        return line
    # Insert a newline and a tab after each "&&"
    return re.sub(r'\s*&&\s*', r' &&\n\t', line)

def format_document(doc: str, *, color: bool = False) -> str:
    # Process each line from the original file.
    formatted = '\n'.join([process_line(line) for line in doc.splitlines()])

    if color:
        # brackets (these have to come first)
        formatted = formatted.replace("[", "\033[37m[\033[0m")
        formatted = formatted.replace("]", "\033[37m]\033[0m")
        formatted = formatted.replace("(", "\033[37m(\033[0m")
        formatted = formatted.replace(")", "\033[37m)\033[0m")
        formatted = formatted.replace("{", "\033[37m{\033[0m")
        formatted = formatted.replace("}", "\033[37m}\033[0m")

        # keywords + operators
        formatted = formatted.replace("==", "\033[91m==\033[0m")
        formatted = formatted.replace("<=", "\033[91m<=\033[0m")
        formatted = formatted.replace(">=", "\033[91m>=\033[0m")
        formatted = formatted.replace("!=", "\033[91m!=\033[0m")
        formatted = formatted.replace("&&", "\033[91m&&\033[0m")
        formatted = formatted.replace("||", "\033[91m||\033[0m")
        formatted = formatted.replace(" < ", " \033[91m<\033[0m ")
        formatted = formatted.replace(" > ", " \033[91m>\033[0m ")
        formatted = formatted.replace("?", "\033[91m?\033[0m")
        formatted = formatted.replace("$", "\033[91m$\033[0m")
        formatted = formatted.replace("assume", "\033[91massume\033[0m")
        formatted = formatted.replace("ensures", "\033[91mensures\033[0m")

        # this
        formatted = formatted.replace("this", "\033[0;33mthis\033[0m")


    return formatted 

type Filter = Callable[[str], bool]

def default_filter(line: str) -> bool:
    return "!in" in line
    
def filter_document(doc: list[str], filter: Filter) -> list[str]:
    # Now, split the formatted content into physical lines, filter out any line containing '!in'
    return [line for line in doc if not filter(line)]

def generate_cex(dfy_file: Path):
    """
    Generates a counterexample for the given Dafny file.

    Args:
        dfy_file (str): The path to the Dafny file.
    """
    # Run Dafny to generate a counterexample.
    result = subprocess.run(
        [
            "dafny",
            "verify",
            "--extract-counterexample",
            dfy_file,
        ],
        capture_output=True,
        text=True,
    )

    # Extract the counterexample from the output.
    output = (result.stdout + result.stderr)

    print(format_document(output, color=True))

def main():
    parser = argparse.ArgumentParser(
        description="Generate a counterexample for a Dafny file."
    )
    parser.add_argument("dfy_file", help="Path to the Dafny file")
    args = parser.parse_args()

    generate_cex(Path(args.dfy_file))

if __name__ == "__main__":
    main()