import os
import xml.etree.ElementTree as ET
import re


def generate_vscode_snippets():

    def get_dir_snippets_with_extension(dir, extension):

        paths = os.walk(dir)

        good_paths = []

        for path in paths:

            for file in path[2]:

                if len(file) >= len(extension) and file[-len(extension) :] == extension:

                    good_paths.append(os.path.join(path[0], file))

        return good_paths

    def delete_starting_and_ending_lines(lines):

        new_lines = lines.copy()

        while new_lines[0] == "\n":

            new_lines = new_lines[1:]

        while new_lines[-1] == "\n":

            new_lines = new_lines[:-1]

        return new_lines

    def get_code(lines):

        lines = delete_starting_and_ending_lines(lines)[2:-6]

        for i in range(len(lines)):

            lines[i] = lines[i][:-1]

            for j in reversed(range(len(lines[i]))):

                if lines[i][j] == '"':

                    lines[i] = lines[i][:j] + '\\"' + lines[i][j + 1 :]

                elif lines[i][j] == "'":

                    lines[i] = lines[i][:j] + "\\'" + lines[i][j + 1 :]

                elif lines[i][j] == "\t":

                    lines[i] = lines[i][:j] + "\\\t" + lines[i][j + 1 :]

                elif lines[i][j] == "\\":

                    lines[i] = lines[i][:j] + "\\\\" + lines[i][j + 1 :]

        return lines

    def get_command(lines):

        return delete_starting_and_ending_lines(lines)[-4][16:-14]

    def normalize_name(name):

        name += "_"

        new_name = ""

        temp_name = ""

        for i in range(len(name)):

            if name[i] != "_":

                temp_name += name[i]

            else:

                if len(temp_name) > 0:

                    if len(new_name) == 0:

                        new_name += temp_name.capitalize()

                    else:

                        new_name += " " + temp_name.capitalize()

                    temp_name = ""

        return new_name

    extension = ".sublime-snippet"
    new_extension = ".code-snippets"

    folder = "Sublime-snippets"
    new_folder = "VSCode-snippets"

    if os.path.exists(new_folder):
        os.system(f"rm -r {new_folder}")
    os.system("cp -r " + folder + " " + new_folder)

    path = get_dir_snippets_with_extension(new_folder, extension)

    for file_path in path:

        file = open(file_path, "r")

        lines = file.readlines()

        file.close()

        code = get_code(lines)

        command = get_command(lines)

        name = normalize_name(command)

        text = ""

        text += "{\n"
        text += '\t"' + name + '": {\n'
        text += '\t\t"scope": "cpp",\n'
        text += '\t\t"prefix": "' + command + '",\n'
        text += '\t\t"body": [\n'

        for line in code:

            text += '\t\t\t"' + line + '",\n'

        text += "\t\t],\n"
        text += '\t\t"description": "' + name + '"\n'
        text += "\t}\n"
        text += "}\n"

        os.remove(file_path)

        file = open(file_path[: -len(extension)] + new_extension, "w")

        print(file_path[: -len(extension)] + new_extension)

        file.write(text)

        file.close()


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
    <!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
    <tabTrigger>{tab_trigger}</tabTrigger>
    <!-- Optional: Set a scope to limit where the snippet will trigger -->
    <!-- <scope>source.python</scope> -->
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
        os.system(f"rm -r {target_dir}")
    os.system(f"cp -r {source_dir} {target_dir}")

    snippets_dir = "Sublime-snippets"
    if os.path.exists(snippets_dir):
        process_snippets_directory(snippets_dir)
    else:
        print(f"Directory '{snippets_dir}' not found.")


generate_sublime_snippets()
generate_vscode_snippets()
