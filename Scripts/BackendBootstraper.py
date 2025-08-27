import os
import shutil
import argparse

def main():
    parser = argparse.ArgumentParser(
        description="Bootstraps a new backend."
    )
    parser.add_argument("name", help="Backend's name")
    parser.add_argument("fn_name", help="Backend's function names")
    args = parser.parse_args()

    base_name = "Template"
    src_dir = os.path.abspath("Backend" + base_name)
    dest_dir = os.path.abspath("../Sources/Backends/" + args.name)

    if not os.path.isdir(src_dir):
        raise SystemExit(f"Source directory '{base_name}' not found in current path.")

    if os.path.exists(dest_dir):
        raise SystemExit(f"Destination already exists: {dest_dir}")

    fn_name = args.fn_name
    name = args.name
    name_upper = name.upper()

    # Copy template directory
    shutil.copytree(src_dir, dest_dir)

    # Walk through destination and replace names/contents
    for root, dirs, files in os.walk(dest_dir, topdown=False):
        # Process files
        for fname in files:
            fpath = os.path.join(root, fname)

            # Replace contents in text files
            try:
                with open(fpath, "rb") as fb:
                    head = fb.read(2048)
                is_binary = b"\x00" in head
            except Exception:
                is_binary = True

            if not is_binary:
                try:
                    with open(fpath, "r", encoding="utf-8") as f:
                        text = f.read()
                    new_text = text.replace("TemplateName", fn_name).replace("TEMPLATE", name_upper).replace("Template", name)
                    if new_text != text:
                        with open(fpath, "w", encoding="utf-8") as f:
                            f.write(new_text)
                except UnicodeDecodeError:
                    pass

            # Rename file if needed
            new_fname = fname.replace("TEMPLATE", name_upper).replace("Template", name)
            if new_fname != fname:
                os.replace(fpath, os.path.join(root, new_fname))

        # Process directories
        for dname in dirs:
            old_dpath = os.path.join(root, dname)
            new_dname = dname.replace("TEMPLATE", name_upper).replace("Template", name)
            if new_dname != dname:
                os.replace(old_dpath, os.path.join(root, new_dname))

    print(f"✅ Project created at: {dest_dir}")

if __name__ == '__main__':
    main()
