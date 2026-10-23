# ETS Robotika - Laporan Riset Kit iMCLab

Ringkasan riset: kit iMCLab (motor DC dengan sensor kecepatan, dikendalikan ESP32) dipelajari dalam empat tahap. Tahap pertama adalah kendali dasar lewat Arduino IDE: ON/OFF, pengaturan kecepatan dengan PWM, dan kedap-kedip tanpa `delay()`. Tahap kedua memindahkan kendali ke laptop memakai Python (`pyserial`) di Jupyter Notebook, termasuk deteksi port ESP32 otomatis. Tahap ketiga menghubungkan kit ke cloud Blynk IoT sehingga motor dapat dikendalikan dan RPM dipantau dari web dan aplikasi HP. Tahap keempat mempelajari pembaruan program nirkabel (OTA) dengan ArduinoOTA lewat WiFi dan OTA lewat web server dalam mode Access Point (ESP2SOTA).

## Daftar modul

| No | Modul | Tujuan | Folder | Laporan |
|---|---|---|---|---|
| 1 | Basic robotika dengan Kit iMCLab | Mengendalikan LED dan motor (ON/OFF, naik-turun PWM, kedap-kedip) lewat Serial Monitor | [Modul1_Basic_Robotika_iMCLab](Modul1_Basic_Robotika_iMCLab/) | [README.md](Modul1_Basic_Robotika_iMCLab/README.md) |
| 2 | Python dengan Kit iMCLab | Mengendalikan kit dari Python lewat serial USB dan mendeteksi port otomatis | [Modul2_Python_iMCLab](Modul2_Python_iMCLab/) | [README.md](Modul2_Python_iMCLab/README.md) |
| 3 | iMCLab berbasis Blynk | Mengendalikan motor dan memantau RPM dari web dan aplikasi lewat cloud | [Modul3_Blynk_iMCLab](Modul3_Blynk_iMCLab/) | [README.md](Modul3_Blynk_iMCLab/README.md) |
| 4 | OTA | Memperbarui program ESP32 lewat WiFi (ArduinoOTA dan web server) | [Modul4_OTA_Blynk](Modul4_OTA_Blynk/) | [README.md](Modul4_OTA_Blynk/README.md) |

## Ringkasan hasil

| Modul | Hasil utama |
|---|---|
| 1 | Motor dan LED dikendalikan lewat Serial Monitor. Kedap-kedip berbasis `millis()` dengan interval 100 ms selama 5 detik menghasilkan 25 kedipan, dan perintah `0` tetap dapat membatalkannya. |
| 2 | Port ESP32 terdeteksi otomatis sebagai `COM6` (CH9102, VID:PID 1A86:55D4). Semua perintah (ON/OFF, naik-turun, PWM langsung, kedap-kedip) berhasil dikirim dari Python. |
| 3 | Kit tersambung ke Blynk Cloud dan dikendalikan dari web serta aplikasi. Slider (V2) dan tombol (V3) mengendalikan motor, gauge menampilkan RPM (V0) dan PWM (V1). |
| 4 | Update lewat WiFi berhasil dengan ArduinoOTA (kedipan LED 250 ms menjadi 1000 ms tanpa kabel USB) dan lewat web server pada `10.10.10.1/update` memakai berkas `.bin`. |

## Sketch, notebook, dan firmware per modul

| Modul | Berkas |
|---|---|
| 1 | `on_off_Motor.ino`, `imclab_naik_turun.ino`, `kedap_kedip_Motor.ino` |
| 2 | `Test_Port_Serial.ipynb`, `Tes_IMCLab_pilih_port_otomatis.ipynb`, `Tes_IMCLab_naik_turun.ipynb`, `Tes_IMCLab_kedap_kedip.ipynb` |
| 3 | `imclab_Blynk_kelas.ino` |
| 4 | `BasicOTA.ino`, `AP_Mode.ino`, firmware `AP_Mode/firmware/AP_Mode.ino.bin` |

## Perangkat

| Komponen | Keterangan |
|---|---|
| Kit | iMCLab (motor DC, driver, sensor RPM, LED indikator) |
| Mikrokontroler | ESP32, board Arduino IDE: DOIT ESP32 DEVKIT V1 (chip USB-UART CH9102, `COM6`) |
| Perangkat lunak | Arduino IDE 2.3.10, Python 3 + `pyserial` 3.5, Jupyter Notebook |
| Cloud | Blynk IoT (web console dan aplikasi mobile) |
| Library OTA | `ArduinoOTA` (bawaan ESP32 core) dan `ESP2SOTA` |

## Catatan keamanan

Kredensial (token Blynk, password WiFi, password OTA, password access point) disimpan di `secrets.h` pada folder sketch masing-masing dan tidak di-push. Yang ada di repositori hanya `secrets.example.h` berisi nilai pengganti. Salin menjadi `secrets.h` dan isi sendiri sebelum upload.

## Referensi

1. Rahmat, B. dan Muljono. *Pemrograman Internet of Things (IoT) dengan Arduino dan Python, Jilid 1*. CV Eureka Media Aksara.
2. Rahmat, B. *Integrasi AI dan IoT pada Sistem Kendali Cerdas* (materi kuliah), dan repositori kode kit iMCLab `github.com/bsrahmat/imclab`.
3. Dokumentasi Espressif (ESP32), Blynk IoT, `pyserial`, dan Jupyter.