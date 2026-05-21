# bacicle_computer
ESP32 priject
```mermaid
graph TD
    %% --- ספק כוח ---
    subgraph Power_Supply [ספק כוח - מורכב על השילדה]
        Battery[סוללת ליתיום נטענת <br/> (Li-Ion 3.7V)] --> BMS[מעגל טעינה והגנה <br/> (TP4056)]
        BMS --> Regulator[מייצב מתח 3.3V <br/> (LDO)]
    end

    Regulator ==>|מתח הפעלה| ESP32
    Regulator --> Sensors
    Regulator --> Display

    %% --- תשומות / חיישנים ---
    subgraph Sensors [יחידת חיישנים]
        SpeedSens[חיישן מהירות <br/> (אפקט הול + מגנט על השילדה/גלגל)] -->|פולסים| ESP32
        CadenceSens[חיישן קדנס - קצב דיווש <br/> (אפקט הול + מגנט על הדוושה)] -->|פולסים| ESP32
        Button[כפתור הפעלה/איפוס <br/> (על הכידון)] -->|לחיצה| ESP32
    end

    %% --- עיבוד מרכזי ---
    subgraph Controller [בקר מרכזי - על הכידון]
        ESP32[<b>בקר ESP32</b> <br/> עיבוד נתונים, מדידת זמנים, ניהול BLE]
    end

    %% --- תפוקות / ממשק ---
    subgraph Outputs [ממשק משתמש - על הכידון]
        ESP32 -->|פרוטוקול I2C| Display[מסך OLED/LCD <br/> (הצגת מהירות, מרחק, קדנס בזמן אמת)]
    end

    %% --- תקשורת חכמה ---
    subgraph Cloud_App [תקשורת וסמארטפון]
        ESP32 -.->|Bluetooth BLE| Smartphone[אפליקציית סמארטפון <br/> (Blynk/App Inventor/Strava)]
        Smartphone -.->|Wi-Fi/Cellular| Cloud[שמירת היסטוריית רכיבות ב-Cloud <br/> (Google Sheets/Firebase)]
    end

    %% אופציה להרחבה
    subgraph GPS_Option [הרחבה אופציונלית]
        GPS[רכיב GPS] -.->|UART| ESP32
    end

    %% הגדרות ויזואליות
    style ESP32 fill:#f96,stroke:#333,stroke-width:2px,color:white
    style Power_Supply fill:#eee,stroke:#bbb
    style Sensors fill:#e1f5fe,stroke:#81d4fa
    style Outputs fill:#e8f5e9,stroke:#a5d6a7
    style Cloud_App fill:#fff3e0,stroke:#ffcc80,stroke-dasharray: 5 5

```
