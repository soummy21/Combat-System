# 🥊 Combat-System
*A modular third-person combat system built in Unreal Engine 5.*

---

## 🎮 Gameplay Overview
This project showcases a foundational combat system built in Unreal Engine 5 using a component-based architecture extending the blueprint system with c++. Designed for extensibility and clarity, it enables chaining of combos, stamina-based mechanics, responsive input handling, and clean player-enemy interactions.

---

## ⚙️ Systems Design

### 🧱 Component-Based Architecture
All gameplay features are structured as reusable components to promote clean, maintainable code and rapid prototyping.

- **Combat Component**  
  Handles attack logic, cooldowns, and stamina usage

- **Player Actions Component**  
  Manages auxiliary player interactions such as walking and sprinting

- **Trace Component**  
  Executes attack hit detection using line/sphere traces and broadcasts hit events.

- **Lock-On Component**  
  Enables lock-on targeting mechanics, smoothly rotating the character toward targets and toggling between them.

- **Block Component**  
  Allows the player to block incoming attacks and react accordingly (e.g., stagger, reduce damage).

- **Stats Component**  
  Manages player stats like health, damage and stamina, including regeneration

---

## 🧠 Architecture & Code Patterns

### 🧩 Design Patterns Used

- **Component Pattern**: All major systems like Health, Combat, and Stats are modular components that can be attached to both players and the boss.
- **Observer Pattern**: Used to broadcast key events like health or stamina changes to other systems (e.g., UI updates, notifing damage and health).
- **Custom Interfaces**: Player and enemy interactions are mediated via Unreal Interfaces to reduce tight coupling and enable plug-and-play functionality.

---

## 🎮 Controls

| Action           | Key / Button   |
|------------------|----------------|
| Attack           | Left Mouse     |
| Sprint           | Shift          |
| Lock-On          | Tab            |

---
