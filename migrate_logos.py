#!/usr/bin/env python3
"""
Скрипт для миграции логотипов из fastfetch в speedfetch
Копирует все ASCII логотипы и их цвета
"""

import os
import re
from pathlib import Path
from collections import defaultdict

# Пути
FASTFETCH_LOGO_DIR = Path("/home/vlad/Загрузки/fastfetch-dev/src/logo")
SPEEDFETCH_SRC_DIR = Path("/home/vlad/Загрузки/speedfetch/src")
BUILTIN_C = FASTFETCH_LOGO_DIR / "builtin.c"

def read_ascii_art(filename):
    """Читает ASCII арт из файла"""
    filepath = FASTFETCH_LOGO_DIR / "ascii" / f"{filename}.txt"
    if filepath.exists():
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()
                return content
        except Exception as e:
            print(f"Error reading {filepath}: {e}")
            return ""
    return ""

def extract_logo_metadata():
    """Извлекает метаданные логотипов из builtin.c"""
    with open(BUILTIN_C, 'r', encoding='utf-8') as f:
        content = f.read()
    
    logos = {}
    
    # Найти все блоки логотипов
    # Ищем паттерн: // DistroName { ...colors... }
    
    logo_blocks = re.findall(
        r'//\s*(.+?)\n\s*\{\s*\.names\s*=\s*\{([^}]+)\}.*?\.colors\s*=\s*\{([^}]+)\}',
        content,
        re.DOTALL
    )
    
    for distro_name, names_section, colors_section in logo_blocks:
        distro_name = distro_name.strip()
        
        # Извлечь имена
        names = re.findall(r'"([^"]+)"', names_section)
        
        # Извлечь цвета
        colors = re.findall(r'FF_COLOR_FG_(\w+(?:\s+"[^"]*")?)', colors_section)
        colors = [c.strip() for c in colors]
        
        # Первое имя используется для имени файла
        filename = names[0].lower().replace(' ', '_').replace('/', '_').replace('-', '_') if names else distro_name.lower()
        
        logos[distro_name] = {
            'names': names,
            'colors': colors,
            'filename': filename
        }
    
    return logos

def get_all_logo_files():
    """Получает список всех файлов логотипов"""
    ascii_dir = FASTFETCH_LOGO_DIR / "ascii"
    files = []
    for f in ascii_dir.iterdir():
        if f.is_file() and f.suffix == '.txt':
            files.append(f.stem)
    return sorted(files)

def escape_string_for_cpp(s):
    """Экранирует строку для C++ raw string"""
    # Для raw strings нам нужно только экранировать скобки
    if ')' in s and '"' in s:
        # Если есть )" найти безопасный разделитель
        return s
    return s

def color_to_cpp(color_str):
    """Конвертирует цвет в C++ формат"""
    color_str = color_str.strip()
    
    if not color_str:
        return 'COLOR_DEFAULT'
    
    # Маппинг цветов
    color_map = {
        'DEFAULT': 'COLOR_DEFAULT',
        'RED': 'COLOR_RED',
        'GREEN': 'COLOR_GREEN',
        'YELLOW': 'COLOR_YELLOW',
        'BLUE': 'COLOR_BLUE',
        'MAGENTA': 'COLOR_MAGENTA',
        'CYAN': 'COLOR_CYAN',
        'WHITE': 'COLOR_WHITE',
        'BLACK': 'COLOR_BLACK',
        'LIGHT_RED': 'COLOR_LIGHT_RED',
        'LIGHT_GREEN': 'COLOR_LIGHT_GREEN',
        'LIGHT_YELLOW': 'COLOR_LIGHT_YELLOW',
        'LIGHT_BLUE': 'COLOR_LIGHT_BLUE',
        'LIGHT_MAGENTA': 'COLOR_LIGHT_MAGENTA',
        'LIGHT_CYAN': 'COLOR_LIGHT_CYAN',
    }
    
    # Проверка на 256-color формат
    if '256' in color_str:
        match = re.search(r'256\s*"([^"]+)"', color_str)
        if match:
            return f'COLOR_256_{match.group(1)}'
    
    # Простой цвет
    for key, val in color_map.items():
        if key in color_str.upper():
            return val
    
    return 'COLOR_DEFAULT'

def generate_cpp_code(logos_dict, all_files):
    """Генерирует C++ код с логотипами"""
    
    cpp_code = """#include "ascii_art.h"
#include <algorithm>

// Color definitions
enum class LogoColor {
    COLOR_DEFAULT,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
    COLOR_BLACK,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_YELLOW,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_MAGENTA,
    COLOR_LIGHT_CYAN,
};

struct LogoInfo {
    std::string art;
    std::vector<LogoColor> colors;
};

"""
    
    # Генерируем данные логотипов
    cpp_code += "const std::map<std::string, LogoInfo> ASCIIArt::arts = {\n"
    
    processed = set()
    
    for filename in all_files:
        # Читаем ASCII арт
        ascii_content = read_ascii_art(filename)
        if not ascii_content.strip():
            continue
        
        # Пытаемся найти информацию в метаданных
        logo_info = None
        best_match = None
        
        for distro_name, info in logos_dict.items():
            if info['filename'] == filename:
                logo_info = info
                best_match = distro_name
                break
        
        # Если не找到, используем filename как ключ
        if not logo_info:
            logo_info = {
                'names': [filename],
                'colors': ['DEFAULT'],
                'filename': filename
            }
            best_match = filename.replace('_', ' ').title()
        
        key = logo_info['filename']
        if key in processed:
            continue
        processed.add(key)
        
        # Обработка цветов
        colors_list = []
        for color in logo_info['colors'][:5]:  # Максимум 5 цветов
            colors_list.append(color_to_cpp(color))
        if not colors_list:
            colors_list = ['COLOR_DEFAULT']
        
        colors_cpp = ", ".join(colors_list)
        
        # Экранизация контента
        escaped_content = ascii_content.replace('\\', '\\\\').replace('"', '\\"')
        
        # Добавляем в карту
        cpp_code += f'    {{"{key}", {{\n'
        cpp_code += f'        R"({escape_string_for_cpp(ascii_content)})",\n'
        cpp_code += f'        {{{colors_cpp}}}\n'
        cpp_code += f'    }}}},\n'
    
    cpp_code += "};\n"
    
    return cpp_code

def main():
    print("Начинаю миграцию логотипов из fastfetch...")
    
    # Получаем все логотипы
    all_files = get_all_logo_files()
    print(f"Найдено {len(all_files)} файлов логотипов")
    
    # Извлекаем метаданные
    print("Извлекаю метаданные из builtin.c...")
    logos_dict = extract_logo_metadata()
    print(f"Найдено {len(logos_dict)} логотипов с метаданными")
    
    # Генерируем C++ код
    print("Генерирую C++ код...")
    cpp_code = generate_cpp_code(logos_dict, all_files)
    
    # Сохраняем новый файл
    output_file = SPEEDFETCH_SRC_DIR / "ascii_art_full.cpp"
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(cpp_code)
    
    print(f"✓ Код сохранён в {output_file}")
    print(f"✓ Обработано {len(all_files)} логотипов")

if __name__ == "__main__":
    main()
