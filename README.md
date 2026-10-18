# HID Keyboard Brightness

Мод для [Windhawk](https://windhawk.net/): клавиши **Brightness Up / Brightness Down** на клавиатуре меняют яркость **внешних мониторов** через DDC/CI в Windows 10/11.

Windows умеет менять яркость только у экранов ноутбуков. На настольном ПК клавиши яркости обычно ничего не делают (или только двигают ползунок на экране). Мод слушает эти клавиши напрямую и отправляет яркость на все подключённые DDC/CI-мониторы.

Изначально написано для личного использования. Код создан с помощью ИИ, работоспособность проверена мной. Поддержки не планируется. Предоставляется «как есть», без каких-либо гарантий. Используйте на свой риск.

## Возможности

- **Одно нажатие — один шаг** (по умолчанию 10 %, как деления ползунка Windows 11).
- **Удержание** — автоповтор с настраиваемой задержкой и интервалом, чтобы монитор шёл в темпе системного ползунка.
- **Привязка к сетке**: яркость округляется до кратных шагу значений (0, 10, 20 … 100), поэтому монитор и ползунок Windows доходят до краёв одновременно.
- **Шаги по часам**: если монитор отвечает на запись по 150 мс, пропущенные шаги объединяются в одну запись, итоговое значение остаётся верным.
- **Самовосстановление**: мониторы определяются заново после смены дисплеев, сна и ошибок записи.
- Работает со **всеми** DDC/CI-мониторами сразу.
- Не тормозит запуск `explorer.exe`.

## Требования

- Windows 10 или 11, установленный [Windhawk](https://windhawk.net/)
- Внешний монитор с **включённым DDC/CI** (проверьте в экранном меню монитора)
- Клавиатура, которая отправляет клавиши яркости как HID *Consumer Control* (`0x6F` и `0x70`)

## Установка

1. Установите Windhawk.
2. В Windhawk нажмите **Create a new mod**, замените шаблон содержимым файла [`hid-keyboard-brightness.wh.cpp`](hid-keyboard-brightness.wh.cpp) и нажмите **Compile Mod**.
3. Включите мод. Он работает внутри `explorer.exe`.

## Настройки

| Параметр | По умолчанию | Описание |
|---|---|---|
| Step per key press | `10` | Шаг в процентах (1–50) |
| Invert direction | выкл | Поменять Up и Down местами |
| Snap to step grid | вкл | Округлять до кратных шагу значений |
| Auto-repeat while key is held | вкл | Повторять шаги при удержании |
| Repeat start delay (ms) | `125` | Через сколько начнётся автоповтор |
| Repeat interval (ms) | `325` | Интервал между повторами |

### Подгонка под скорость ползунка Windows

Зажмите клавишу и засеките, за сколько ползунок Windows проходит путь от 0 до 100 %. Время примерно равно:

```
всего ≈ задержка + 9 × интервал
```

Подберите *Repeat start delay* и *Repeat interval*, чтобы монитор и ползунок доходили до края одновременно. Значения по умолчанию подбирались на одной клавиатуре, у вас может понадобиться небольшая правка.

## Ограничения

- Только **внешние DDC/CI-мониторы**; встроенные панели ноутбуков не управляются.
- Мод **не может прочитать или изменить системный ползунок Windows** (публичного API нет), он лишь повторяет его шаг и скорость.
- Клавиши, которые обрабатываются прошивкой/ACPI ноутбука, как HID-отчёты не видны и работать не будут.
- Скорость DDC/CI зависит от монитора; на некоторых при удержании яркость меняется рывками.

## Диагностика

Откройте лог мода в Windhawk:

| Строка в логе | Значение |
|---|---|
| `raw input registered` | Прослушивание клавиатуры работает |
| `rescan: N DDC/CI display(s)` | Сколько мониторов найдено. `0` — DDC/CI выключен или не поддерживается |
| `press up` / `press down` | Клавиша доходит до мода |
| `HidP_GetUsages failed` | Не удалось разобрать отчёт клавиатуры |
| `SetVCPFeature failed` | Монитор отклонил запись, запланировано пересканирование |

Если строк `press up/down` нет, клавиатура, скорее всего, не присылает эти клавиши как HID Consumer Control.

---

# English version

A [Windhawk](https://windhawk.net/) mod that lets the **Brightness Up / Brightness Down** keys of your keyboard control the brightness of **external monitors** over DDC/CI on Windows 10/11.

Windows only changes brightness for laptop panels. If you have a desktop PC or an external monitor, the brightness keys on your keyboard usually do nothing (or only move the on-screen slider). This mod listens to those keys directly and sends the brightness to every connected DDC/CI monitor.

Originally written for personal use. Created with AI assistance — I've tested it and confirmed it works. No support planned. Provided "as is", without warranties. Use at your own risk.

## Features

- **One press = one step** (default 10 %, matching the 10-segment Windows 11 slider).
- **Hold to repeat** with a configurable delay and interval, so the monitor can follow the speed of the Windows brightness flyout.
- **Grid snapping**: brightness is rounded to multiples of the step (0, 10, 20 … 100), so the monitor and the Windows slider reach both ends together.
- **Clock-based stepping**: if a slow monitor needs 150 ms per DDC write, missed steps are merged into one write, so the final value is always correct.
- **Self-healing**: monitors are re-detected after a display change, sleep, or a failed write.
- **Multi-monitor**: all DDC/CI monitors are adjusted together.
- Does not block `explorer.exe` startup (monitor detection runs in a background thread).

## Requirements

- Windows 10 or 11
- [Windhawk](https://windhawk.net/) installed
- An external monitor with **DDC/CI enabled** (check the monitor's OSD menu)
- A keyboard that sends the brightness keys as HID *Consumer Control* usages `0x6F` (Brightness Increment) and `0x70` (Brightness Decrement)

## Installation

1. Install Windhawk.
2. In Windhawk, click **Create a new mod**, replace the template with the contents of [`hid-keyboard-brightness.wh.cpp`](hid-keyboard-brightness.wh.cpp), and click **Compile Mod**.
3. Enable the mod. It runs inside `explorer.exe`.

## Settings

| Setting | Default | Description |
|---|---|---|
| Step per key press | `10` | Step size in percent (1–50) |
| Invert direction | off | Swap Up and Down |
| Snap to step grid | on | Round to multiples of the step |
| Auto-repeat while key is held | on | Keep stepping while the key is down |
| Repeat start delay (ms) | `125` | Hold time before auto-repeat starts |
| Repeat interval (ms) | `325` | Time between repeated steps |

### Matching the Windows flyout speed

Hold the key and time how long the Windows slider takes to go from 0 to 100 %. That time is roughly:

```
total ≈ delay + 9 × interval
```

Adjust *Repeat start delay* and *Repeat interval* until the monitor and the slider reach the end at the same moment. The defaults were tuned on one keyboard, so a small correction may be needed on yours.

## Limitations

- Only **external DDC/CI monitors**. Laptop internal panels are not controlled.
- The mod **cannot read or change the Windows brightness flyout**; there is no public API for it. It only imitates its step size and speed.
- Keys handled purely by laptop firmware/ACPI are not visible as HID reports and will not work.
- DDC/CI speed depends on the monitor; some monitors move in jumps when a key is held.

## Troubleshooting

Open the mod's log in Windhawk and look for:

| Log line | Meaning |
|---|---|
| `raw input registered` | Keyboard listener is active |
| `rescan: N DDC/CI display(s)` | Number of monitors found. `0` means DDC/CI is off or unsupported |
| `press up` / `press down` | The key reaches the mod |
| `HidP_GetUsages failed` | The keyboard report could not be parsed |
| `SetVCPFeature failed` | The monitor rejected the write; a rescan is scheduled |

If there is no `press up/down` line, your keyboard likely does not send these keys as HID Consumer Control reports.
