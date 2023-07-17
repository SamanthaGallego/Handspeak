# HandSpeak - Real-Time Sign Language Communication with AI

HandSpeak is a revolutionary project aimed at breaking down communication barriers between people who use sign language and those who do not. It leverages cutting-edge technology and AI algorithms to translate sign language gestures in real-time, fostering inclusivity and equal opportunities in interactions.

## Features
- Real-time translation of sign language gestures
- Intuitive and user-friendly glove interface
- AI-powered classification of 5 sign language words: fine, hello, sorry, thankyou, and yes
- Arduino classifier for ESP32 with MPU6050 sensor support

## How it Works
1. **Data Collection**: HandSpeak was trained on a dataset containing 5 classes of sign language gestures using an ESP32 with an MPU6050 sensor to capture hand movements.

2. **Model Architecture**: The AI model is a sequential neural network with dense layers and ReLU activation for the first two layers. The last layer uses softmax activation for multi-class classification.

3. **Training**: The model is compiled with the RMSprop optimizer and Mean Squared Error (MSE) as the loss function. It was trained for 100 epochs with a batch size of 1. A validation set was used to monitor performance.

4. **Real-Time Translation**: The intelligent glove captures hand gestures and sends them to the AI model, which classifies the gestures into one of the 5 sign language words. The translation is then displayed via the glove interface.

## Repository Contents
- `/Arduino_Classifier`: Contains the Arduino classifier code to be uploaded to an ESP32 with an MPU6050 sensor.

## Getting Started
1. Set up the hardware: Connect the MPU6050 sensor to the ESP32 board.

2. Upload the classifier code to the ESP32 using the Arduino IDE.

3. Wear the HandSpeak glove and make sign language gestures.

4. Observe the real-time translation on the glove's interface and witness the magic of communication without barriers.

## Contributing
We welcome contributions to improve HandSpeak and make it even more inclusive and effective. Please fork this repository and submit pull requests.

## Acknowledgments
We would like to thank all contributors and supporters who made HandSpeak possible. Together, let's create a future where communication is free and accessible to all.
