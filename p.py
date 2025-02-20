import os
import xml.etree.ElementTree as ET


def process_snippet_file(file_path):
    try:
        tree = ET.parse(file_path)
        root = tree.getroot()

        content = root.find("content").text.strip()
        tab_trigger_element = root.find("tabTrigger")

        if tab_trigger_element is None:
            print(f"Skipping {file_path}: No tabTrigger found.")
            return

        tab_trigger = tab_trigger_element.text.strip()
        cpp_content = f'// TAB_TRIGGER "{tab_trigger}"\n\n{content}'

        new_file_path = file_path.replace(".sublime-snippet", ".cpp")
        with open(new_file_path, "w", encoding="utf-8") as cpp_file:
            cpp_file.write(cpp_content)

        os.remove(file_path)
        print(f"Converted {file_path} -> {new_file_path}")
    except Exception as e:
        print(f"Error processing {file_path}: {e}")


def process_snippets_directory(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".sublime-snippet"):
                file_path = os.path.join(root, file)
                process_snippet_file(file_path)


if __name__ == "__main__":
    snippets_dir = "Code"
    if os.path.exists(snippets_dir):
        process_snippets_directory(snippets_dir)
    else:
        print(f"Directory '{snippets_dir}' not found.")
