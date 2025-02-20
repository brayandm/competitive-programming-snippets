import os
import shutil
import xml.etree.ElementTree as ET
import re


def generate_vscode_snippets():
    def get_dir_snippets_with_extension(directory, extension):
        good_paths = []
        for root, _, files in os.walk(directory):
            for file in files:
                if file.endswith(extension):
                    good_paths.append(os.path.join(root, file))
        return good_paths

    def delete_starting_and_ending_lines(lines):
        new_lines = lines[:]
        while new_lines and new_lines[0] == "\n":
            new_lines = new_lines[1:]
        while new_lines and new_lines[-1] == "\n":
            new_lines = new_lines[:-1]
        return new_lines

    def get_code(lines):
        lines = delete_starting_and_ending_lines(lines)[2:-6]

        for i in range(len(lines)):
            lines[i] = lines[i].rstrip()
            lines[i] = lines[i].replace('"', '\\"')
            lines[i] = lines[i].replace("'", "\\'")
            lines[i] = lines[i].replace("\t", "\\t")
            lines[i] = lines[i].replace("\\", "\\\\")

        return lines

    def get_command(lines):
        return delete_starting_and_ending_lines(lines)[-4][16:-14]

    def normalize_name(name):
        name += "_"
        new_name = ""
        temp_name = ""
        for char in name:
            if char != "_":
                temp_name += char
            else:
                if temp_name:
                    if not new_name:
                        new_name = temp_name.capitalize()
                    else:
                        new_name += " " + temp_name.capitalize()
                    temp_name = ""
        return new_name

    extension = ".sublime-snippet"
    new_extension = ".code-snippets"

    folder = "Sublime-snippets"
    new_folder = "VSCode-snippets"

    if os.path.exists(new_folder):
        shutil.rmtree(new_folder)
    shutil.copytree(folder, new_folder)

    paths = get_dir_snippets_with_extension(new_folder, extension)

    for file_path in paths:
        with open(file_path, "r", encoding="utf-8") as file:
            lines = file.readlines()

        code = get_code(lines)
        command = get_command(lines)
        name = normalize_name(command)

        text = """
{
    "%s": {
        "scope": "cpp",
        "prefix": "%s",
        "body": [
%s        ],
        "description": "%s"
    }
}
""" % (
            name,
            command,
            "\n".join(f'        "{line}",' for line in code).rstrip(","),
            name,
        )

        os.remove(file_path)
        new_file_path = file_path[: -len(extension)] + new_extension
        with open(new_file_path, "w", encoding="utf-8") as file:
            file.write(text)
        print(f"Converted {file_path} -> {new_file_path}")


def generate_sublime_snippets():
    def process_snippet_file(file_path):
        try:
            with open(file_path, "r", encoding="utf-8") as cpp_file:
                lines = cpp_file.readlines()

            tab_trigger = None
            content_lines = []

            for line in lines:
                match = re.match(r"// TAB_TRIGGER \"(.+)\"", line)
                if match:
                    tab_trigger = match.group(1)
                else:
                    content_lines.append(line)

            if tab_trigger is None:
                print(f"Skipping {file_path}: No TAB_TRIGGER comment found.")
                return

            content = "".join(content_lines).strip()

            snippet_content = f"""<snippet>
    <content><![CDATA[
{content}
]]></content>
    <tabTrigger>{tab_trigger}</tabTrigger>
</snippet>"""

            new_file_path = file_path.replace(".cpp", ".sublime-snippet")
            with open(new_file_path, "w", encoding="utf-8") as snippet_file:
                snippet_file.write(snippet_content)

            os.remove(file_path)
            print(f"Converted {file_path} -> {new_file_path}")
        except Exception as e:
            print(f"Error processing {file_path}: {e}")

    def process_snippets_directory(directory):
        for root, _, files in os.walk(directory):
            for file in files:
                if file.endswith(".cpp"):
                    file_path = os.path.join(root, file)
                    process_snippet_file(file_path)

    source_dir = "Code"
    target_dir = "Sublime-snippets"

    if os.path.exists(target_dir):
        shutil.rmtree(target_dir)
    shutil.copytree(source_dir, target_dir)

    snippets_dir = "Sublime-snippets"
    if os.path.exists(snippets_dir):
        process_snippets_directory(snippets_dir)
    else:
        print(f"Directory '{snippets_dir}' not found.")


generate_sublime_snippets()
generate_vscode_snippets()
