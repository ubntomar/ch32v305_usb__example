# USB CDC Example for CH32V305FBP6 (USB HS)
# Ejemplo USB CDC para CH32V305FBP6 (USB HS)

[English](#english) | [Español](#español)

---
## English

### Important

This example is specific to the CH32V305FBP6, which ONLY has a USB HS (High Speed) controller.
Unlike other models in the family, this IC does not have USB FS (Full Speed).

### Features

- Basic USB CDC device implementation using USB HS
- Sends "Hello World" every 5 seconds
- Code specific for CH32V305FBP6
- Bilingual comments (English/Spanish)

### Required Hardware

- CH32V305FBP6 microcontroller
- USB connection to PC

### Connections

- USB D+ -> PB7
- USB D- -> PB6

### Setup

1. Configure your IDE (MounRiver Studio recommended)
2. Compile and flash the code
3. Connect the device via USB
4. Device will appear as a COM port
5. Use any serial terminal (like PuTTY) configured at 9600 baud

### Troubleshooting

1. If device doesn't enumerate:
   - Check USB connections (PB6/PB7)
   - Ensure drivers are installed
   - Verify you're using USB HS examples (not FS)
   
2. If no data is visible:
   - Check terminal configuration (9600 8N1)
   - Make sure device is properly enumerated

---
## Español

### Importante

Este ejemplo es específico para el CH32V305FBP6, que SOLO cuenta con controlador USB HS (High Speed).
A diferencia de otros modelos de la familia, este IC no dispone de USB FS (Full Speed).

### Características

- Implementación de dispositivo USB CDC básico usando USB HS
- Envía "Hola Mundo" cada 5 segundos
- Código específico para CH32V305FBP6
- Comentarios bilingües (Español/Inglés)

### Hardware Necesario

- Microcontrolador CH32V305FBP6
- Conexión USB a PC

### Conexiones

- USB D+ -> PB7
- USB D- -> PB6

### Configuración

1. Configure su IDE (MounRiver Studio recomendado)
2. Compile y flashee el código
3. Conecte el dispositivo vía USB
4. El dispositivo aparecerá como puerto COM
5. Use cualquier terminal serial (como PuTTY) configurado a 9600 baudios

### Solución de Problemas

1. Si el dispositivo no enumera:
   - Verifique las conexiones USB (PB6/PB7)
   - Asegúrese de que los drivers estén instalados
   - Verifique que está usando los ejemplos de USB HS (no FS)
   
2. Si no ve datos:
   - Verifique la configuración del terminal (9600 8N1)
   - Asegúrese de que el dispositivo esté enumerado correctamente

---
## Common Sections / Secciones Comunes

### References / Referencias
- [CH32V305 Documentation](http://www.wch-ic.com/products/CH32V305.html)
- [USB CDC Specification](https://www.usb.org/documents)
- [Original Repository by UBNTOMAR](https://github.com/UBNTOMAR)

### License / Licencia
This project is under Apache 2.0 license. See LICENSE file for details.
Este proyecto está bajo la licencia Apache 2.0. Ver el archivo LICENSE para más detalles.

### Credits / Créditos
- Original Author / Autor Original: UBNTOMAR
- Based on WCH official examples / Basado en los ejemplos oficiales de WCH