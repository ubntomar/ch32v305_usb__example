# Technical Guide - USB CDC Example CH32V305
# Guía Técnica - Ejemplo USB CDC CH32V305

[🇬🇧 English Version](#english-technical-guide) | [🇪🇸 Versión en Español](#guía-técnica-en-español)

---
# English Technical Guide

## Table of Contents
1. [Basic Concepts](#1-basic-concepts)
2. [Project Structure](#2-project-structure)
3. [Key Components](#3-key-components)
4. [Practical Examples](#4-practical-examples)
5. [Common Debugging](#5-common-debugging)
6. [Additional Resources](#6-additional-resources)

## 1. Basic Concepts

### 1.1 What is USB CDC?
USB CDC (Communications Device Class) is a standard that allows a USB device to behave as a serial port. When you connect the device to your PC:
- It appears as a virtual COM port
- You can communicate with it using any serial terminal
- No special drivers required (uses standard system CDC drivers)

Example:
```
PC (Terminal) <---> USB <---> CH32V305 (our device)
        COM3 <------> Virtual Serial Port
```

### 1.2 USB HS vs USB FS
- FS (Full Speed): 12 Mbps
- HS (High Speed): 480 Mbps
- CH32V305FBP6 only has USB HS
- Configuration is different from USB FS, which is why many generic examples don't work

[Continue with full English section...]

---
# Guía Técnica en Español

## Tabla de Contenidos
1. [Conceptos Básicos](#1-conceptos-básicos)
2. [Estructura del Proyecto](#2-estructura-del-proyecto)
3. [Componentes Clave](#3-componentes-clave)
4. [Ejemplos Prácticos](#4-ejemplos-prácticos)
5. [Depuración Común](#5-depuración-común)
6. [Recursos Adicionales](#6-recursos-adicionales)

## 1. Conceptos Básicos

### 1.1 ¿Qué es USB CDC?
USB CDC (Communications Device Class) es un estándar que permite que un dispositivo USB se comporte como un puerto serial. Cuando conectas el dispositivo a tu PC:
- Aparece como un puerto COM virtual
- Puedes comunicarte con él usando cualquier terminal serial
- No requiere drivers especiales (usa los CDC estándar del sistema)

Ejemplo:
```
PC (Terminal) <---> USB <---> CH32V305 (nuestro dispositivo)
        COM3 <------> Puerto Serie Virtual
```

### 1.2 USB HS vs USB FS
- FS (Full Speed): 12 Mbps
- HS (High Speed): 480 Mbps
- CH32V305FBP6 solo tiene USB HS
- La configuración es diferente a USB FS, por eso muchos ejemplos genéricos no funcionan

[Continuar con sección completa en español...]

---
# Common References / Referencias Comunes

## Documentation / Documentación
- [CH32V305 Manual](link)
- [USB CDC Specification](link)
- [WCH Official Website](link)

## Tools / Herramientas
1. MounRiver Studio IDE
2. USB Protocol Analyzer
3. Serial Terminal (PuTTY, TeraTerm)
4. Oscilloscope