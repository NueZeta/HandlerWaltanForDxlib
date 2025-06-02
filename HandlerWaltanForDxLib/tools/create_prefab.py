import os
import json
import re
import sys


def scan_registered_prefabs(scan_file_path):

    with open(scan_file_path, "r", encoding="utf-8") as f:
        source = f.read()

    # DEFINE_PREFAB(名前) { コンポーネント, コンポーネント, ... }
    pattern = re.compile(
        r'/\*\s*DEFINE_PREFAB\s*\(\s*(\w+)\s*\)\s*\{([^}]+)\}\s*\*/',
        re.MULTILINE | re.DOTALL)

    prefabs = []

    for match in pattern.finditer(source):
        name = match.group(1)
        body = match.group(2).strip()

        lines = [line.strip() for line in body.splitlines() if line.strip() and not line.strip().startswith("//")]

        #最初の三行を数値として抽出

        try:
            pos   = [float(x.strip()) for x in lines[0].split(',') if x.strip()]
            rot   = [float(x.strip()) for x in lines[1].split(',') if x.strip()]
            scale = [float(x.strip()) for x in lines[2].split(',') if x.strip()]
        except (IndexError, ValueError) as e:
            print(f"Error parsing numeric values in prefab '{name}': {e}")
            continue


        # 各行を処理してコンポーネント名を取得
        components = []
        for line in lines[3:]:
            comps = [comp.strip() for comp in line.split(',') if comp.strip()]
            components.extend(comps)        

        prefabs.append({
            "name": name,
            "position": pos,
            "rotation": rot,
            "scale": scale,
            "components": components
        })

    return prefabs





def main():

    # スクリプトのあるディレクトリ
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # 出力先のパス
    output_dir = os.path.abspath(os.path.join(script_dir, "../generated/Prefabs"))
    # 検索するprefab.hのパス
    prefab_header = os.path.abspath(os.path.join(script_dir, "../src/Prefab.h"))

    # ファイルが存在しない場合は終了
    if not os.path.exists(prefab_header):
        print(f"prefab.h not found")
        sys.exit(0)  # 終了

    # 出力先ディレクトリがなければ作成
    os.makedirs(output_dir, exist_ok=True)

    # プレハブのスキャン
    prefabs = scan_registered_prefabs(prefab_header)

    for prefab in prefabs:
        prefab_file = os.path.join(output_dir, f"{prefab['name']}.prefab.json")
        with open(prefab_file, "w", encoding="utf-8") as f:
            json.dump(prefab, f, indent=2)
        print(f"Output: {prefab_file}")

if __name__ == "__main__":
    main()