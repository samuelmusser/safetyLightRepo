# safetyLightRepo
🌞 🚥 ⛈️
The Safety Light is an embedded, solar-powered, microcontrolled light along road lines that help drivers see the road in unpleasent conditions all the while communicating temperature data to road signs.

👨‍💻
The software side of the project is an implementation of power saving features, temperature data recording, processing, parsing, and finally the networking between itself and the receiver on the road sign. The receiver will be intaking data from multiple safety lights, averaging the data, possibly displaying a message, and telling the safety lights how long to turn off to save power.

🥅 Responsibilities
Chris Bharucha: Power Saving, Temperature Sensor n\
Sam Musser: Networking, Communication Parsing, and Encryption n\
David Gilstad: Overview, User Manual n\

📖Libraries Used
Standard C libraries 
Arduino LoRa library by sandeepmistry (MIT LICENSE)
