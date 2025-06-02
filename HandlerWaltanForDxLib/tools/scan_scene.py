import os
import json
import re
import sys

def scan_registered_scenes(scan_dir):
    registered_scenes = []
    pattern = re.compile(r'REGISTER_SCENE\s*\(\s*"([^"]+)"\s*,\s*(\w+)\s*\)')

    for root, _, files in os.walk(scan_dir):
        for file in files:
            if file.endswith(".cpp") or file.endswith(".h"):
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, "r", encoding="utf-8") as f:
                        content = f.read()
                        matches = pattern.findall(content)
                        for scene_name, _ in matches:
                            registered_scenes.append(scene_name)
                except Exception as e:
                    print(f"ファイル読み込みに失敗しました: {filepath}, {e}")

    return list(set(registered_scenes))  # 重複除去

def main():
    if len(sys.argv) < 2:
        print("出力先ディレクトリを引数で指定してください。")
        return

    # スクリプトのあるディレクトリ（絶対パス）
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # Pythonスクリプトのパス
    output_dir = os.path.abspath(os.path.join(script_dir,  "../generated/Scenes"))
    # 検索するディレクトリのパス
    src_dir = os.path.abspath(os.path.join(script_dir,  "../src/Scenes"))


    # 同ディレクトリ内のファイルをすべて削除
    for filename in os.listdir(output_dir):
        file_path = os.path.join(output_dir, filename)
        # ファイルのみ削除（ディレクトリは除く）
        if os.path.isfile(file_path):
            os.remove(file_path)

    os.makedirs(output_dir, exist_ok=True)

    scenes = scan_registered_scenes(src_dir)

    for scene_name in scenes:
        scene_data = {
            "sceneName": scene_name
        }
        output_path = os.path.join(output_dir, f"{scene_name}.scene.json")
        with open(output_path, "w", encoding="utf-8") as f:
            json.dump(scene_data, f, indent=4)
        print(f"output file => {output_path} ")

if __name__ == "__main__":
    main()
