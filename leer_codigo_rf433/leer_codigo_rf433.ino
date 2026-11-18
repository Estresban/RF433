#include <RCSwitch.h>

// Crear la instancia de la librería
RCSwitch miReceptor = RCSwitch();

void setup() {
  Serial.begin(9600);
  
  // Habilitar la recepción en la interrupción 0 (asociada al Pin Digital 2 en Arduino Uno/Nano)
  miReceptor.enableReceive(0);  
  
  Serial.println("--- Receptor RF 433MHz Inicializado ---");
  Serial.println("Esperando señal de un mando o transmisor...");
}

void loop() {
  // Comprobar si se ha recibido y decodificado un paquete de datos
  if (miReceptor.available()) {
    
    // 1. Obtener el valor numérico del código (en formato decimal)
    unsigned long codigoRecibido = miReceptor.getReceivedValue();
    
    // Si el valor es 0, significa que la señal recibida no es compatible o tiene ruido
    if (codigoRecibido == 0) {
      Serial.println("Error: Código desconocido o señal corrupta.");
    } else {
      // 2. Mostrar la información decodificada en el Monitor Serie
      Serial.print("Código Decimal: ");
      Serial.println(codigoRecibido);
      
      Serial.print("Longitud de bits: ");
      Serial.print(miReceptor.getReceivedBitlength());
      Serial.println(" bits");
      
      Serial.print("Protocolo detectado: ");
      Serial.println(miReceptor.getReceivedProtocol());
      
      Serial.print("Retardo de pulso (Pulse Length): ");
      Serial.print(miReceptor.getReceivedDelay());
      Serial.println(" µs");
      
      Serial.println("----------------------------------------");
    }

    // 3. Resetear el receptor para permitir la captura de la siguiente señal
    miReceptor.resetAvailable();
  }
}

