# Unreal Engine 5 – GAS Crash Course

### What this is
This project comes from me revisiting the **Gameplay Ability System (GAS)** in Unreal Engine 5.6, following Stephen Ulibarri’s Udemy course.  
It’s not a game — it’s a sandbox for learning how GAS actually works under the hood. I’m using it to rebuild my muscle memory with the framework and to keep my C++ and UE workflow sharp.

---

### Why it exists
I’ve worked with Unreal before, but GAS always felt like one of those systems that’s easy to *use badly*. This repo is me taking the time to understand it properly — attributes, gameplay effects, prediction, replication — the whole deal.

If you’re an employer or another developer looking at this:  
The goal here isn’t flashy gameplay. It’s **clarity and correctness** — solid architecture, clean comments, and a working understanding of how Unreal expects you to structure abilities.

---

### What it shows
- Attribute sets for core stats (health, stamina, etc.)
- Ability activation and input binding  
- Gameplay effects (damage, buffs, debuffs)
- Network prediction and replication logic  
- Blueprint ↔ C++ integration (clean handoffs, no spaghetti)

---

### Tech setup
| Component | Detail |
|------------|---------|
| **Engine** |![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.6-black?logo=unrealengine)|
| **Language** | ![C++](https://img.shields.io/badge/Language-C%2B%2B-blue) |
| **Focus** | GAS architecture and reproducible gameplay logic |
| **Platform** | Windows (tested in-editor only) |

---

### Running it
1. Clone this repo  
   ```bash
   git clone https://github.com/BurntShrimpDev/Crash-Course.git

---
### Notes
This is a learning project, not a production system.
Some code is directly inspired by (or adapted from) Stephen Ulibarri’s course for educational purposes. I’ve reworked and extended pieces to test ideas and document the why behind decisions. Comments in the code call out what changed and why.

---
### References

- Stephen Ulibarri — Unreal GAS Crash Course (Udemy): https://www.udemy.com/course/ue5-gas-crash-course

- Epic Games — Gameplay Ability System docs: https://docs.unrealengine.com/5.0/en-US/gameplay-ability-system-in-unreal-engine/
