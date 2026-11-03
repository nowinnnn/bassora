# BASSORA – 808 & bass generator (JUCE 8)

Monofoniczny syntezator basów / 808: 2 oscylatory z tablicami fal (wavetable), LFO z synchronizacją do tempa,
4 makra, EQ i kompresor na wyjściu, ponad 120 presetów w kategoriach oraz własne presety użytkownika.
Formaty: VST3, Standalone (Windows), AU (macOS, budowanie lokalne).

## Instalator z GitHuba (Windows)

Instalator `BASSORA-Setup-<wersja>.exe` buduje GitHub Actions (`.github/workflows/release.yml`) – nie trzeba nic instalować lokalnie.

1. Utwórz puste repozytorium na GitHubie (np. `bassora`) i wypchnij do niego ten folder:

       git init
       git add .
       git commit -m "BASSORA 0.4.0"
       git branch -M main
       git remote add origin https://github.com/TWOJA-NAZWA/bassora.git
       git push -u origin main

   Każdy push na `main` buduje instalator i zapisuje go jako artefakt (zakładka **Actions** → ostatni przebieg → **Artifacts**).

2. Żeby opublikować wydanie, które każdy pobierze ze strony repozytorium (**Releases**), wypchnij tag z numerem wersji:

       git tag v0.4.0
       git push origin v0.4.0

   Workflow zbuduje wtyczkę, złoży instalator i dołączy go do nowego wydania.

Budowanie trwa kilka–kilkanaście minut (JUCE kompiluje się od zera). Windows SmartScreen może ostrzegać przy pierwszym
uruchomieniu, bo instalator nie jest podpisany certyfikatem – „Więcej informacji” → „Uruchom mimo to”.

### Instalator lokalnie
Wymagane: CMake ≥ 3.22, Visual Studio 2022 (C++), [Inno Setup 6](https://jrsoftware.org/isdl.php). Uruchom `make-installer.bat`
(wynik: `dist\BASSORA-Setup-<wersja>.exe`).

Instalator kopiuje VST3 do `C:\Program Files\Common Files\VST3\` i (opcjonalnie) Standalone do `Program Files\BASSORA`.
Własne presety użytkownika leżą w `%APPDATA%\BASSORA\Presets` i zostają po odinstalowaniu.

## Budowanie ręczne

    cmake -B build
    cmake --build build --config Release

JUCE 8.0.4 pobiera się automatycznie (FetchContent). Domyślnie po zbudowaniu VST3 kopiuje się do systemowego folderu
pluginów; wyłączysz to przez `-DBASSORA_COPY_AFTER_BUILD=OFF`. Wersję ustawia `-DBASSORA_VERSION=1.2.3`.

## Presety

Fabryczne presety generuje `tools/gen_presets.py` do `Source/FactoryPresets.h` (kategorie: 808, Sub & Boom, Distorted,
Trap & Slides, Reese & Neuro, Wobble & Dubstep, Growl & Vowel, Pluck & Short, Synth Bass, Wavetable Morph, FX & Experimental).
Edytujesz skrypt, uruchamiasz `python tools/gen_presets.py` i budujesz ponownie – skrypt sprawdza zakresy wartości.
Własne presety: przycisk **Save** w nagłówku wtyczki (lista „My presets”), **Delete** usuwa wybrany.

## Wydania

- **0.4.0** – wygląd w stylu logo (czerń, srebro, zimny blask), >120 presetów w kategoriach, instalator + GitHub Actions.
- **0.3.0** – własne presety, LFO tempo-sync, wavetable (13 kształtów + Morph), EQ i kompresor, skalowane okno.

Uwaga licencyjna: JUCE jest na GPLv3 lub licencji komercyjnej – do sprzedaży BASSORY potrzebna jest licencja JUCE.
