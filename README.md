# Convex Hull Calculator

תוכנית C++ לחישוב המעטפת הקמורה (Convex Hull) של קבוצת נקודות במישור.

## מבנה הפרויקט

```
ex3_system/
├── src/
│   ├── main.cpp           # התוכנית הראשית
│   └── convex_hull.cpp    # יישום אלגוריתם המעטפת הקמורה
├── include/
│   └── convex_hull.h      # הגדרות וכותרות
├── input/
│   └── points.txt         # קובץ קלט לדוגמה
├── output/
│   └── result.txt         # קובץ פלט (נוצר אוטומטית)
├── tests/
├── obj/                   # קבצי אובייקט (נוצר אוטומטית)
└── Makefile

## איך להריץ

### קומפיילציה
```bash
make
```

### הרצה עם קובץ ברירת מחדל
```bash
make run
```

### הרצה עם קובץ מותאם אישית
```bash
make run-custom INPUT=path/to/input.txt OUTPUT=path/to/output.txt
```

### או ישירות:
```bash
./convex_hull input/points.txt output/result.txt
```

## פורמט קובץ הקלט

השורה הראשונה: מספר הנקודות
השורות הבאות: זוגות של קואורדינטות x y

דוגמה:
```
4
0.0 0.0
0.0 1.0
1.0 1.0
2.0 0.0
```

## פורמט קובץ הפלט

השורה הראשונה: מספר הנקודות במעטפת הקמורה
השורות הבאות: נקודות המעטפת הקמורה בסדר נגד כיוון השעון

## אלגוריתם

התוכנית משתמשת באלגוריתם Andrew's Monotone Chain עם מורכבות זמן O(n log n).

## ניקוי

```bash
make clean
```
