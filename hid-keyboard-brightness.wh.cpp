// ==WindhawkMod==
// @id              hid-keyboard-brightness
// @name            HID Keyboard Brightness
// @description     Яркость внешних мониторов (DDC/CI) клавишами яркости клавиатуры / Control external monitor brightness (DDC/CI) with the keyboard's HID Brightness keys
// @version         1.0
// @author          YOUR_NAME
// @github          https://github.com/YOUR_NAME
// @homepage        https://github.com/YOUR_NAME/hid-keyboard-brightness
// @include         explorer.exe
// @compilerOptions -lhid -ldxva2
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# HID Keyboard Brightness

## Русский

Клавиши **Brightness Up / Brightness Down** на USB/Bluetooth-клавиатуре
меняют яркость ваших **внешних мониторов** через DDC/CI.

Клавиши читаются напрямую из HID-интерфейса *Consumer Control* клавиатуры
(Raw Input), дополнительные программы не нужны. Яркость меняется сразу на
всех подключённых DDC/CI-мониторах.

### Возможности
- Одно нажатие — один шаг (по умолчанию 10 %, как на ползунке Windows 11).
- Удержание клавиши — автоповтор с настраиваемым темпом, чтобы монитор
  успевал за системным ползунком яркости.
- Яркость привязана к сетке шага (0, 10, 20 … 100), поэтому монитор и
  ползунок Windows доходят до краёв одновременно.
- Шаги считаются по часам, а не по числу записей в DDC: если медленный
  монитор тратит 150 мс на запись, пропущенные шаги применяются одной
  записью, и итоговое значение остаётся верным.
- Мониторы автоматически определяются заново после смены дисплеев, сна
  или неудачной записи.

### Настройки
| Параметр | По умолчанию | Описание |
|---|---|---|
| Step per key press | 10 | Шаг в процентах (1–50) |
| Invert direction | выкл | Поменять Up и Down местами |
| Snap to step grid | вкл | Округлять до кратных шагу значений |
| Auto-repeat while key is held | вкл | Повторять шаги при удержании |
| Repeat start delay (ms) | 125 | Через сколько начнётся автоповтор |
| Repeat interval (ms) | 325 | Интервал между повторами |

#### Подгонка под скорость ползунка Windows
Зажмите клавишу и засеките, за сколько ползунок Windows проходит путь от
0 до 100 %. Время примерно равно `задержка + 9 × интервал`. Подберите оба
значения так, чтобы монитор и ползунок доходили до края одновременно.
Значения по умолчанию подбирались на одной клавиатуре, у вас может
понадобиться небольшая правка.

### Примечания и ограничения
- Только внешние мониторы с DDC/CI (включите его в экранном меню
  монитора). Встроенные панели ноутбуков не управляются.
- Мод не может прочитать или изменить системный ползунок яркости Windows,
  он лишь повторяет его шаг и скорость.
- Клавиатура должна присылать клавиши как HID Consumer Control:
  Brightness Increment (0x6F) / Decrement (0x70). Клавиши, которые
  обрабатываются прошивкой/ACPI ноутбука, моду не видны.

### Написано с помощью ИИ
Код в основном сгенерирован ИИ. Активной поддержки не планируется.

---

## English

Makes the **Brightness Up / Brightness Down** keys of a USB/Bluetooth
keyboard control the brightness of your **external monitors** over DDC/CI.

The keys are read directly from the keyboard's HID *Consumer Control*
interface (Raw Input), so no other software is needed. All connected
DDC/CI monitors are adjusted at the same time.

### Features
- One key press = one step (default 10 %, like the Windows 11 slider).
- Holding the key auto-repeats at a configurable pace, so the monitor
  can follow the Windows brightness flyout.
- Brightness is snapped to a grid of the step size (0, 10, 20 ... 100),
  so the monitor and the Windows slider reach both ends together.
- Steps are counted by the clock, not by the number of DDC writes: if a
  slow monitor needs 150 ms per write, the missed steps are applied in
  one go and the final value is still correct.
- Monitors are re-detected automatically after a display change, sleep
  or a failed write.

### Settings
| Setting | Default | Description |
|---|---|---|
| Step per key press | 10 | Step size in percent (1-50) |
| Invert direction | off | Swap Up and Down |
| Snap to step grid | on | Round to multiples of the step |
| Auto-repeat while key is held | on | Keep stepping while the key is down |
| Repeat start delay (ms) | 125 | Hold time before auto-repeat starts |
| Repeat interval (ms) | 325 | Time between repeated steps |

#### Matching the Windows flyout speed
Time the Windows slider from 0 to 100 % while holding the key. It is
roughly `delay + 9 x interval`. Adjust the two repeat values until the
monitor and the slider reach the end at the same moment. The defaults
were tuned on one keyboard and may need a small correction on yours.

### Notes and limitations
- Only external monitors that support DDC/CI (enable it in the monitor's
  OSD menu). Laptop internal panels are not controlled.
- The mod cannot read or change the Windows brightness flyout. It only
  mimics its step size and speed.
- Your keyboard must send the keys as HID Consumer Control usages
  Brightness Increment (0x6F) / Decrement (0x70). Keys handled purely by
  laptop firmware/ACPI are not visible to this mod.

### Written with AI
Most of the code was generated by AI. No active maintenance is planned.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- stepPercent: 10
  $name: Шаг на нажатие / Step per key press (%)
  $description: От 1 до 50 / 1 to 50
- invertDirection: false
  $name: Инвертировать направление / Invert direction
  $description: Включите, если Brightness Up затемняет экран / Enable if Brightness Up makes the screen darker
- snapToGrid: true
  $name: Привязка к сетке шага / Snap to step grid
  $description: Округлять яркость до кратных шагу значений (10, 20, 30...) как ползунок Windows / Round brightness to multiples of the step (10, 20, 30...) like the Windows slider
- autoRepeat: true
  $name: Автоповтор при удержании / Auto-repeat while key is held
  $description: Выключите, если нужен ровно один шаг на нажатие / Turn off if you want exactly one step per key press
- repeatDelayMs: 125
  $name: Задержка до автоповтора (мс) / Repeat start delay (ms)
  $description: Сколько держать клавишу до начала автоповтора / How long to hold the key before auto-repeat starts
- repeatIntervalMs: 325
  $name: Интервал автоповтора (мс) / Repeat interval (ms)
  $description: Время между шагами при удержании (меньше = быстрее) / Time between repeated steps while holding (lower = faster)
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <hidsdi.h>
#include <hidpi.h>
#include <lowlevelmonitorconfigurationapi.h>
#include <physicalmonitorenumerationapi.h>

#include <atomic>
#include <chrono>
#include <map>
#include <mutex>
#include <thread>
#include <vector>

// ---------------------------------------------------------------------------
// Константы и общее состояние
// Constants and shared state
// ---------------------------------------------------------------------------

constexpr USHORT kUsagePageConsumer = 0x0C;
constexpr USHORT kUsageBrightnessUp = 0x6F;    // Brightness Increment
constexpr USHORT kUsageBrightnessDown = 0x70;  // Brightness Decrement
constexpr BYTE kVcpBrightness = 0x10;          // MCCS VCP-код: Luminance / MCCS VCP code: Luminance

// Если клавиша «удерживается» дольше этого времени, считаем, что отчёт об
// отпускании потерялся, и прекращаем повтор.
// If the key looks held for longer than this, assume a release report was
// lost and stop repeating.
constexpr ULONGLONG kMaxHoldMs = 10000;
// Отчёт «удержание», пришедший позже этого срока после предыдущего, считается
// новым нажатием (восстановление после потери отчёта об отпускании).
// A "held" report arriving later than this after the previous one is treated
// as a new press (recovers from a lost release report).
constexpr ULONGLONG kStuckReportMs = 1000;
// Максимум «догоняющих» шагов за одну запись в DDC.
// Upper bound for catch-up steps applied in a single DDC write.
constexpr int kMaxCatchUpTicks = 20;

// Настройки. Атомарные, потому что читаются из нескольких потоков.
// Settings. Atomic because they are read from several threads.
struct {
    std::atomic<int> stepPercent{10};
    std::atomic<bool> invertDirection{false};
    std::atomic<bool> snapToGrid{true};
    std::atomic<bool> autoRepeat{true};
    std::atomic<int> repeatDelayMs{125};
    std::atomic<int> repeatIntervalMs{325};
} settings;

// Один монитор с поддержкой DDC/CI.
// One DDC/CI-capable monitor.
struct Display {
    HANDLE hPhysical = nullptr;  // дескриптор физического монитора / physical monitor handle
    DWORD vcpMax = 100;          // максимум яркости, сообщённый монитором / max brightness reported by the monitor
    DWORD lastRawValue = 0;      // кэш текущего значения / cached current raw value
    bool hasLastRaw = false;     // кэш валиден / true if lastRawValue is valid
};

std::mutex g_displaysMutex;
std::vector<Display> g_displays;

// Потоки и окно.
// Worker threads and window.
std::atomic<bool> g_stop{false};
std::atomic<DWORD> g_threadId{0};
std::atomic<HWND> g_hwnd{nullptr};
HANDLE g_threadHandle = nullptr;  // поток цикла сообщений (Raw Input) / message-loop thread (Raw Input)
std::thread g_repeatThread;       // единственный поток, работающий с DDC/CI / the only thread that talks DDC/CI

// Состояние клавиши. HandleRawInput (поток сообщений) только пишет эти
// переменные; RepeatThread читает их и делает весь DDC/CI-трафик. Так не
// бывает двойных записей и не нужно ограничение частоты.
// Key state. HandleRawInput (message thread) only writes these variables;
// RepeatThread reads them and does all DDC/CI traffic. This avoids double
// writes and any need for rate limiting.
std::atomic<USHORT> g_heldUsage{0};         // 0 = нет, либо Up/Down / 0 = none, or Up/Down usage
std::atomic<HANDLE> g_heldDevice{nullptr};  // устройство, приславшее нажатие / device that sent the press
std::atomic<int> g_pendingDelta{0};         // накопленное изменение в % / accumulated change in percent
std::atomic<bool> g_needRead{true};         // перечитать реальное значение при след. записи / re-read the real value on next write
std::atomic<ULONGLONG> g_pressTick{0};      // момент последнего нового нажатия / tick of the latest new press
std::atomic<ULONGLONG> g_lastReportTick{0}; // момент последнего отчёта «удержание» / tick of the latest "held" report
std::atomic<bool> g_rescanNeeded{true};     // мониторы нужно найти заново / monitors must be re-enumerated
std::atomic<ULONGLONG> g_lastRescanTick{0};

// ---------------------------------------------------------------------------
// DDC/CI
// ---------------------------------------------------------------------------

static BOOL CALLBACK CollectMonitorProc(HMONITOR h, HDC, LPRECT, LPARAM lp) {
    reinterpret_cast<std::vector<HMONITOR>*>(lp)->push_back(h);
    return TRUE;
}

// Закрывает все дескрипторы мониторов и очищает список.
// Closes all physical monitor handles and clears the list.
void ReleaseMonitors() {
    std::lock_guard<std::mutex> lock(g_displaysMutex);
    for (auto& d : g_displays) {
        if (d.hPhysical) {
            PHYSICAL_MONITOR pm{};
            pm.hPhysicalMonitor = d.hPhysical;
            DestroyPhysicalMonitors(1, &pm);
            d.hPhysical = nullptr;
        }
    }
    g_displays.clear();
}

// Читает текущую и максимальную яркость. DDC/CI иногда отвечает ошибкой с
// первого раза, поэтому пробуем несколько раз.
// Reads the current and maximum brightness. DDC/CI sometimes fails on the
// first try, so retry a few times.
bool ReadBrightness(HANDLE h, DWORD& current, DWORD& maximum) {
    for (int attempt = 0; attempt < 3; ++attempt) {
        MC_VCP_CODE_TYPE type{};
        if (GetVCPFeatureAndVCPFeatureReply(h, kVcpBrightness, &type,
                                            &current, &maximum) &&
            maximum > 0) {
            return true;
        }
        Sleep(40);
    }
    return false;
}

// Открывает первый физический монитор за HMONITOR, отвечающий по DDC/CI.
// Opens the first physical monitor behind an HMONITOR that answers DDC/CI.
bool TryAttachMonitor(HMONITOR h, Display& out) {
    DWORD count = 0;
    if (!GetNumberOfPhysicalMonitorsFromHMONITOR(h, &count) || count == 0)
        return false;

    std::vector<PHYSICAL_MONITOR> physical(count);
    if (!GetPhysicalMonitorsFromHMONITOR(h, count, physical.data()))
        return false;

    for (DWORD i = 0; i < count; ++i) {
        DWORD current = 0, maximum = 0;
        if (!out.hPhysical &&
            ReadBrightness(physical[i].hPhysicalMonitor, current, maximum)) {
            out.hPhysical = physical[i].hPhysicalMonitor;
            out.vcpMax = maximum;
            out.lastRawValue = current;
            out.hasLastRaw = true;
            continue;  // этот дескриптор оставляем открытым / keep this handle open
        }
        DestroyPhysicalMonitors(1, &physical[i]);
    }
    return out.hPhysical != nullptr;
}

// Заново перечисляет мониторы и оставляет те, что поддерживают DDC/CI.
// Re-enumerates all monitors and keeps those that support DDC/CI.
void Rescan() {
    Wh_Log(L"rescan: enumerating monitors");
    g_lastRescanTick.store(GetTickCount64());
    ReleaseMonitors();

    std::vector<HMONITOR> monitors;
    EnumDisplayMonitors(nullptr, nullptr, CollectMonitorProc,
                        reinterpret_cast<LPARAM>(&monitors));

    std::vector<Display> found;
    for (HMONITOR h : monitors) {
        Display d;
        if (TryAttachMonitor(h, d)) found.push_back(std::move(d));
    }

    std::lock_guard<std::mutex> lock(g_displaysMutex);
    g_displays = std::move(found);
    Wh_Log(L"rescan: %zu DDC/CI display(s)", g_displays.size());
}

size_t DisplayCount() {
    std::lock_guard<std::mutex> lock(g_displaysMutex);
    return g_displays.size();
}

// Двигает процент по сетке кратных `step` значений `steps` раз
// (положительное = вверх, отрицательное = вниз). Повторяет логику ползунка
// Windows.
// Moves a percentage along a grid of multiples of `step`, `steps` times
// (positive = up, negative = down). Mimics the Windows brightness slider.
static int SnapMove(int pct, int steps, int step) {
    while (steps > 0) {
        pct = (pct / step + 1) * step;
        --steps;
    }
    while (steps < 0) {
        pct = ((pct + step - 1) / step - 1) * step;
        ++steps;
    }
    if (pct < 0) pct = 0;
    if (pct > 100) pct = 100;
    return pct;
}

// Применяет изменение яркости (в процентах) ко всем мониторам.
// forceRead: перечитать реальное значение с монитора, а не брать кэш
// (делается в начале каждого нажатия, чтобы учесть изменения, сделанные
// кнопками самого монитора).
// Возвращает true, если хотя бы один монитор реально изменился.
//
// Applies a brightness change (in percent) to every monitor.
// forceRead: re-read the real value from the monitor instead of using the
// cache (done at the start of every key press, so changes made through the
// monitor's own buttons are picked up).
// Returns true if at least one monitor was actually changed.
bool ApplyDelta(int delta, bool forceRead) {
    std::lock_guard<std::mutex> lock(g_displaysMutex);
    bool anyChanged = false;

    for (auto& d : g_displays) {
        if (!d.hPhysical) continue;

        DWORD current = 0, maximum = 0;
        bool have = false;

        if (forceRead || !d.hasLastRaw) {
            have = ReadBrightness(d.hPhysical, current, maximum);
            if (have) d.vcpMax = maximum;
        }
        // Чтение не удалось (или не требовалось) — берём кэш.
        // Read failed (or was not requested): fall back to the cache.
        if (!have && d.hasLastRaw && d.vcpMax > 0) {
            current = d.lastRawValue;
            maximum = d.vcpMax;
            have = true;
        }
        if (!have) {
            Wh_Log(L"no brightness value, rescan scheduled");
            g_rescanNeeded.store(true);
            continue;
        }

        LONG newVal;
        if (settings.snapToGrid.load()) {
            int step = settings.stepPercent.load();
            int steps = delta / step;
            if (steps == 0) steps = delta > 0 ? 1 : -1;
            int curPct = static_cast<int>(current * 100.0 / maximum + 0.5);
            int pct = SnapMove(curPct, steps, step);
            newVal = static_cast<LONG>(pct * static_cast<double>(maximum) /
                                       100.0 + 0.5);
        } else {
            LONG rawDelta = static_cast<LONG>(maximum) * delta / 100;
            if (rawDelta == 0) rawDelta = delta > 0 ? 1 : -1;
            newVal = static_cast<LONG>(current) + rawDelta;
        }
        if (newVal < 0) newVal = 0;
        if (newVal > static_cast<LONG>(maximum))
            newVal = static_cast<LONG>(maximum);

        if (newVal == static_cast<LONG>(current)) {
            d.lastRawValue = current;
            d.hasLastRaw = true;
            // Уже на 0 или максимуме, писать нечего.
            // Already at 0 or max, nothing to write.
            continue;
        }

        if (SetVCPFeature(d.hPhysical, kVcpBrightness,
                          static_cast<DWORD>(newVal))) {
            d.lastRawValue = static_cast<DWORD>(newVal);
            d.hasLastRaw = true;
            anyChanged = true;
        } else {
            // Дескриптор мог устареть (сон монитора, смена режима).
            // The handle may be stale (monitor sleep, mode change).
            Wh_Log(L"SetVCPFeature failed (%u), rescan scheduled",
                   GetLastError());
            d.hasLastRaw = false;
            g_rescanNeeded.store(true);
        }
    }
    return anyChanged;
}

// ---------------------------------------------------------------------------
// Рабочий поток: единственный, кто пишет в DDC/CI
// Worker thread: the only writer to DDC/CI
// ---------------------------------------------------------------------------

void RepeatThread() {
    Wh_Log(L"repeat thread started");
    // Когда должен произойти следующий шаг автоповтора.
    // When the next auto-repeat step is due.
    ULONGLONG nextRepeatTick = 0;
    // Последнее нажатие, замеченное этим потоком.
    // Last press tick this thread has seen.
    ULONGLONG seenPress = 0;

    while (!g_stop.load()) {
        ULONGLONG now = GetTickCount64();

        // Заново находим мониторы по запросу или если их нет, а клавишу
        // нажали (не чаще раза в 2 с).
        // (Re)detect monitors when requested, or when we have none and a
        // key was pressed (rate limited to once per 2 s).
        bool needScan = g_rescanNeeded.exchange(false);
        if (!needScan && DisplayCount() == 0 &&
            (g_heldUsage.load() != 0 || g_pendingDelta.load() != 0) &&
            now - g_lastRescanTick.load() > 2000) {
            needScan = true;
        }
        if (needScan) {
            Rescan();
            g_needRead.store(true);
        }

        USHORT usage = g_heldUsage.load();
        // Шаг от самого нажатия. / Step from the press itself.
        int pending = g_pendingDelta.exchange(0);

        // Новое нажатие перезапускает таймер автоповтора.
        // A new press restarts the auto-repeat timer.
        ULONGLONG pt = g_pressTick.load();
        if (pt != seenPress) {
            seenPress = pt;
            nextRepeatTick = pt + settings.repeatDelayMs.load();
        }

        if (pending == 0 && usage != 0) {
            ULONGLONG held = now - pt;
            if (held > kMaxHoldMs) {
                Wh_Log(L"hold timeout, forcing release");
                g_heldUsage.store(0);
                continue;
            }
            if (settings.autoRepeat.load() && now >= nextRepeatTick) {
                // Шаги автоповтора считаем по часам, а не по числу
                // завершённых записей в DDC: если запись длится дольше
                // интервала, пропущенные шаги копятся и применяются одной
                // записью.
                // Count repeat steps by the clock, not by completed DDC
                // writes: if one write takes longer than the interval, the
                // missed steps pile up and are applied in a single write.
                int interval = settings.repeatIntervalMs.load();
                int ticks = 0;
                while (now >= nextRepeatTick && ticks < kMaxCatchUpTicks) {
                    nextRepeatTick += interval;
                    ++ticks;
                }
                if (now >= nextRepeatTick) nextRepeatTick = now + interval;
                int step = settings.stepPercent.load();
                pending = ((usage == kUsageBrightnessUp) ? step : -step) * ticks;
            }
        }

        if (pending == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }

        bool forceRead = g_needRead.exchange(false);
        int delta = settings.invertDirection.load() ? -pending : pending;

        ULONGLONG start = GetTickCount64();
        bool wrote = ApplyDelta(delta, forceRead);
        ULONGLONG elapsed = GetTickCount64() - start;

        // Ничего не записано (упёрлись в предел): не крутим холостой цикл.
        // Nothing was written (already at a limit): avoid a busy loop.
        if (!wrote && elapsed < 20) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }

    Wh_Log(L"repeat thread stopped");
}

// ---------------------------------------------------------------------------
// HID Raw Input
// ---------------------------------------------------------------------------

// Preparsed-данные по устройствам, с кэшем (используется только из потока
// сообщений).
// Preparsed data per device, cached (only used from the message thread).
static std::map<HANDLE, std::vector<BYTE>> g_preparsedBuffers;
static std::map<HANDLE, PHIDP_PREPARSED_DATA> g_preparsedPtrs;

PHIDP_PREPARSED_DATA GetPreparsed(HANDLE device) {
    auto it = g_preparsedPtrs.find(device);
    if (it != g_preparsedPtrs.end()) return it->second;

    UINT psize = 0;
    if (GetRawInputDeviceInfoW(device, RIDI_PREPARSEDDATA, nullptr, &psize)
            == UINT(-1) || psize == 0) {
        return nullptr;
    }

    std::vector<BYTE> buf(psize);
    UINT got = psize;
    if (GetRawInputDeviceInfoW(device, RIDI_PREPARSEDDATA, buf.data(), &got)
            == UINT(-1)) {
        return nullptr;
    }

    PHIDP_PREPARSED_DATA ptr =
        reinterpret_cast<PHIDP_PREPARSED_DATA>(buf.data());
    g_preparsedBuffers[device] = std::move(buf);
    g_preparsedPtrs[device] = ptr;
    return ptr;
}

// Разбирает сообщение WM_INPUT и обновляет состояние клавиши.
// Parses a WM_INPUT message and updates the key state.
void HandleRawInput(HRAWINPUT hRawInput) {
    UINT size = 0;
    if (GetRawInputData(hRawInput, RID_INPUT, nullptr, &size,
                        sizeof(RAWINPUTHEADER)) != 0)
        return;
    if (size == 0 || size > 4096) return;

    alignas(8) BYTE buffer[4096];
    if (GetRawInputData(hRawInput, RID_INPUT, buffer, &size,
                        sizeof(RAWINPUTHEADER)) != size)
        return;

    RAWINPUT* ri = reinterpret_cast<RAWINPUT*>(buffer);
    if (ri->header.dwType != RIM_TYPEHID) return;

    HANDLE dev = ri->header.hDevice;
    PHIDP_PREPARSED_DATA preparsed = GetPreparsed(dev);
    if (!preparsed) return;

    HIDP_CAPS caps = {};
    if (HidP_GetCaps(preparsed, &caps) != HIDP_STATUS_SUCCESS) return;
    if (caps.UsagePage != kUsagePageConsumer) return;

    BYTE* data = ri->data.hid.bRawData;
    for (DWORD i = 0; i < ri->data.hid.dwCount; ++i) {
        BYTE* report = data + i * ri->data.hid.dwSizeHid;
        USAGE usages[16];
        ULONG usageCount = 16;
        auto st = HidP_GetUsages(HidP_Input, kUsagePageConsumer, 0, usages,
                                 &usageCount, preparsed,
                                 reinterpret_cast<PCHAR>(report),
                                 ri->data.hid.dwSizeHid);
        if (st == HIDP_STATUS_USAGE_NOT_FOUND) {
            // Пустой отчёт = всё отпущено.
            // Empty report = everything released.
            usageCount = 0;
        } else if (st != HIDP_STATUS_SUCCESS) {
            Wh_Log(L"HidP_GetUsages failed: 0x%08X", (unsigned)st);
            continue;
        }

        USHORT found = 0;
        for (ULONG j = 0; j < usageCount; ++j) {
            if (usages[j] == kUsageBrightnessUp ||
                usages[j] == kUsageBrightnessDown) {
                found = usages[j];
            }
        }

        if (found) {
            ULONGLONG now = GetTickCount64();
            USHORT prev = g_heldUsage.load();
            // Новое нажатие: другая клавиша либо долгая пауза с прошлого
            // отчёта (значит, отчёт об отпускании потерялся).
            // New press: different key, or a long gap since the last report
            // (a release report must have been lost).
            bool isNew = prev != found ||
                         now - g_lastReportTick.load() > kStuckReportMs;
            g_lastReportTick.store(now);

            if (isNew) {
                if (found == kUsageBrightnessUp) {
                    Wh_Log(L"press up");
                } else {
                    Wh_Log(L"press down");
                }
                g_pressTick.store(now);
                g_needRead.store(true);
                g_heldDevice.store(dev);
                g_heldUsage.store(found);
                // Само нажатие — один шаг, остальное делает RepeatThread.
                // The press itself is one step; RepeatThread does the rest.
                int step = settings.stepPercent.load();
                g_pendingDelta.fetch_add(found == kUsageBrightnessUp ? step
                                                                     : -step);
            }
        } else if (g_heldUsage.load() != 0 && g_heldDevice.load() == dev) {
            // В отчёте нет Brightness — значит, клавишу отпустили
            // (или нажали другую consumer-клавишу).
            // The report has no Brightness usage, so the key was released
            // (or another consumer key was pressed).
            Wh_Log(L"release");
            g_heldUsage.store(0);
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_INPUT) {
        HandleRawInput(reinterpret_cast<HRAWINPUT>(lParam));
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    if (msg == WM_DISPLAYCHANGE) {
        // Мониторы изменились — находим их заново.
        // Monitors changed, re-detect them.
        g_rescanNeeded.store(true);
        return 0;
    }
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// Поток цикла сообщений: владеет скрытым окном, получающим Raw Input.
// Message-loop thread: owns a hidden window that receives Raw Input.
DWORD WINAPI ThreadProc(LPVOID) {
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = L"WindhawkHidBrightnessSink";
    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(0, wc.lpszClassName, L"", WS_POPUP,
                                0, 0, 0, 0, nullptr, nullptr,
                                wc.hInstance, nullptr);
    if (!hwnd) return 1;
    g_hwnd.store(hwnd);
    g_threadId.store(GetCurrentThreadId());

    // Получаем HID-отчёты Consumer Control, даже когда окно не в фокусе.
    // Receive HID Consumer Control reports even when we are not focused.
    RAWINPUTDEVICE rid[1] = {};
    rid[0].usUsagePage = kUsagePageConsumer;
    rid[0].usUsage = 0x01;  // Consumer Control
    rid[0].dwFlags = RIDEV_INPUTSINK;
    rid[0].hwndTarget = hwnd;

    if (!RegisterRawInputDevices(rid, 1, sizeof(RAWINPUTDEVICE))) {
        Wh_Log(L"RegisterRawInputDevices failed: %u", GetLastError());
    } else {
        Wh_Log(L"raw input registered");
    }

    MSG msg;
    while (!g_stop.load() && GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    DestroyWindow(hwnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    g_hwnd.store(nullptr);
    return 0;
}

// ---------------------------------------------------------------------------
// Точки входа Windhawk
// Windhawk entry points
// ---------------------------------------------------------------------------

void LoadSettings() {
    int step = Wh_GetIntSetting(L"stepPercent");
    if (step <= 0) step = 10;
    if (step > 50) step = 50;
    settings.stepPercent.store(step);

    settings.invertDirection.store(Wh_GetIntSetting(L"invertDirection") != 0);
    settings.snapToGrid.store(Wh_GetIntSetting(L"snapToGrid") != 0);
    settings.autoRepeat.store(Wh_GetIntSetting(L"autoRepeat") != 0);

    int delay = Wh_GetIntSetting(L"repeatDelayMs");
    if (delay < 0) delay = 0;
    if (delay > 3000) delay = 3000;
    settings.repeatDelayMs.store(delay);

    int interval = Wh_GetIntSetting(L"repeatIntervalMs");
    if (interval < 20) interval = 20;
    if (interval > 2000) interval = 2000;
    settings.repeatIntervalMs.store(interval);
}

BOOL Wh_ModInit() {
    Wh_Log(L"init");
    LoadSettings();

    g_stop.store(false);
    g_heldUsage.store(0);
    g_heldDevice.store(nullptr);
    g_pendingDelta.store(0);
    g_needRead.store(true);
    // Первый поиск мониторов делает RepeatThread, чтобы медленные ответы
    // DDC/CI никогда не тормозили запуск explorer.exe.
    // The first monitor scan is done by RepeatThread so that slow DDC/CI
    // responses never block explorer.exe startup.
    g_rescanNeeded.store(true);

    g_repeatThread = std::thread(RepeatThread);

    g_threadHandle = CreateThread(nullptr, 0, ThreadProc, nullptr, 0, nullptr);
    if (!g_threadHandle) {
        g_stop.store(true);
        if (g_repeatThread.joinable()) g_repeatThread.join();
        return FALSE;
    }
    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L"uninit");
    g_stop.store(true);

    // Останавливаем цикл сообщений.
    // Stop the message loop.
    if (DWORD tid = g_threadId.load())
        PostThreadMessageW(tid, WM_QUIT, 0, 0);
    if (HWND hwnd = g_hwnd.load())
        PostMessageW(hwnd, WM_CLOSE, 0, 0);

    if (g_repeatThread.joinable()) g_repeatThread.join();

    if (g_threadHandle) {
        WaitForSingleObject(g_threadHandle, 5000);
        CloseHandle(g_threadHandle);
        g_threadHandle = nullptr;
    }

    ReleaseMonitors();
    g_threadId.store(0);
    g_hwnd.store(nullptr);
}

void Wh_ModSettingsChanged() {
    Wh_Log(L"settings changed");
    LoadSettings();
}
