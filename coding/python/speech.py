import speech_recognition as sr

rec=open("transcribe.txt","w+")

# Initialize recognizer class (for recognizing the speech)
r = sr.Recognizer()

while(1):
    with sr.Microphone() as source:
        audio_text = r.listen(source)
        # recoginize_() method will throw a request error if the API is unreachable, hence using exception handling
    string=r.recognize_google(audio_text)
    if(string.lower()=="done"):
        break
    else:
        rec.write(string)
        print(string)
