# Camera Proxy ROS 2 Workspace

Kompletny obszar roboczy (workspace) ROS 2 Humble zawierający pakiet `proxy`. Projekt służy do przetwarzania strumienia wideo z wykorzystaniem biblioteki OpenCV oraz mechanizmu `image_transport`.

## Wymagania i Zależności

### Środowisko
* **System operacyjny:** Ubuntu 22.04 LTS (Jammy Jellyfish)
* **Wersja ROS 2:** Humble Hawksbill
* **Język:** C++ 17

### Zależności (pakiety ROS 2)
Projekt wymaga zainstalowania poniższych bibliotek:
* `rclcpp` — standardowa biblioteka C++ dla ROS 2.
* `sensor_msgs` — obsługa wiadomości z czujników i obrazów.
* `cv_bridge` — konwersja między formatami ROS a OpenCV.
* `image_transport` — optymalizacja przesyłu obrazów.
* `opencv` — biblioteka do przetwarzania obrazu.

###Optymalizacja DDS
Aby urządzenie nie zalewało sieci niepotrzebnymi pakietami wymagane jest przeprowadzenie kroków z pliku README_DDS.txt

## Przegląd
Pakiet `proxy` implementuje węzeł pośredniczący w przesyłaniu obrazu. Dla kamery OAK-D, subskrybuje domyślnie publikowany przez nią temat (skompresowany), po czym dla tego samego urządzenia na którym jest uruchomiony publikuje zdekompresowany obraz.

## Struktura Workspace
```text
camera_proxy_workspace/
├── src/
│   └── proxy/                # Pakiet ROS 2
│       ├── src/              # Kod źródłowy (camera_proxy.cpp)
│       ├── CMakeLists.txt    # Konfiguracja kompilacji
│       └── package.xml       # Zależności pakietu
├── .gitignore                # Wykluczenia dla Git (build, install, log)
└── README.md                 # Ta dokumentacja


