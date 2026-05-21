// פינים של ה-ESP32
const int SENSOR_PIN = 4; // החיישן מחובר לפין 4 (אפשר לשנות בהמשך)

// משתנים לחישוב המהירות
volatile int pulseCount = 0;
unsigned long lastTime = 0;
float wheelCircumference = 2.1; // היקף גלגל אופניים ממוצע במטרים (26 אינץ')
float speedKmh = 0.0;

// פונקציית פסיקה (Interrupt) - רצה בכל פעם שהמגנט עובר ליד החיישן
void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  // הפעלת תקשורת טורית למחשב
  Serial.begin(115200);
  
  // הגדרת פין החיישן כקלט עם נגד משיכה פנימי
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  
  // חיבור החיישן לפונקציית הפסיקה - מגיב כשהאות יורד מ-1 ל-0 (FALLING)
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), countPulse, FALLING);
  
  lastTime = millis();
  Serial.println("System Initialized. Waiting for wheel rotation...");
}

void loop() {
  unsigned long currentTime = millis();
  
  // בכל שנייה (1000 מילישניות) נחשב את המהירות
  if (currentTime - lastTime >= 1000) {
    
    // מנתקים זמנית את הפסיקה כדי שלא ישתנו הנתונים בזמן החישוב
    noInterrupts();
    int pulses = pulseCount;
    pulseCount = 0; // מאפסים לספירה הבאה
    interrupts();
    
    // חישוב המרחק שעבר בשנייה האחרונה (מספר סיבובים כפול היקף הגלגל)
    float distanceMeters = pulses * wheelCircumference;
    
    // המרה מקמ"ש (מטרים לשנייה כפול 3.6 הופך לקילומטר לשעה)
    speedKmh = distanceMeters * 3.6;
    
    // הדפסת הנתונים למסך המחשב (Serial Monitor)
    Serial.print("Current Speed: ");
    Serial.print(speedKmh);
    Serial.println(" km/h");
    
    lastTime = currentTime;
  }
}
