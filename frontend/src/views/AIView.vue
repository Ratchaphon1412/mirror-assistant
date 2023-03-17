<template>
  <div class="h-screen text-gray-100 bg-black flex justify-center items-center">
    <div class="row">
      <div v-show="!activeMap" class="flex justify-center">
        <img src="@/assets/images/giphy.gif" class="object-fill h-20 w-20" />
      </div>

      <div class="grid grid-cols-6 gap-4">
        <div></div>
        <div class="col-span-4 text-center self-center">
          <div class="mb-2 text-xl">{{ transcript }}</div>
          <div v-show="activeMap" class="flex justify-center">
            <div v-if="lat != null || long != null">
              <GoogleMap :lat="lat" :long="long" />
            </div>
            <div v-else>
              <GoogleMap />
            </div>
          </div>
        </div>

        <div></div>
      </div>
    </div>

    <!-- <button @click="startListening">Start Listening</button> -->
  </div>
</template>

<script>
import NavbarFooter from "@/layouts/NavbarFooter.vue";
import { useApiStore } from "@/stores/api";
import GoogleMap from "@/components/GoogleMap.vue";
import processMP3 from "@/assets/music/process.mp3";
import off_security from "@/assets/music/off_security.mp3";
import on_security from "@/assets/music/on_security.mp3";
import problem_sound from "@/assets/music/problem_sound.mp3";
import problem_chatGPT from "@/assets/music/problem_chatGPT.mp3";
export default {
  setup() {},
  data() {
    return {
      transcript: "",
      recognition: null,
      apiStore: useApiStore(),
      audio: null,
      lat: null,
      long: null,
      activeMap: false,
    };
  },
  mounted() {
    this.startListening();
  },
  components: {
    NavbarFooter,
    GoogleMap,
  },
  methods: {
    startListening() {
      this.recognition = new webkitSpeechRecognition();
      const thaiLang =
        this.recognition.lang.search("th-") >= 0 ? "th-TH" : "th-TH";
      this.recognition.lang = thaiLang;
      this.recognition.continuous = true;
      this.recognition.interimResults = false;

      this.recognition.onresult = (event) => {
        let interimTranscript = "";
        let finalTranscript = "";
        for (let i = event.resultIndex; i < event.results.length; ++i) {
          const transcript = event.results[i][0].transcript;

          if (event.results[i].isFinal) {
            finalTranscript += transcript;
          } else {
            interimTranscript += transcript;
          }
        }

        // let transcriptResult = finalTranscript || interimTranscript;
        // this.transcript = finalTranscript;

        // this.transcript = interimTranscript;
        // this.doSomething(transcriptResult);
        // if (transcriptResult.startsWith("บอส")) {
        //   // console.log(this.transcript);
        this.doSomething(finalTranscript);
        //   this.doSomething(transcriptResult);
        // }
      };
      this.recognition.onend = () => {
        this.recognition.start();
      };
      this.recognition.start();
    },
    async doSomething(finalTranscript) {
      if (finalTranscript.includes("บอส")) {
        const [, text] = finalTranscript.split("บอส");
        this.transcript = finalTranscript;
        // let text = finalTranscript.replace("บอส", "");
        console.log(text);
        let response = await this.apiStore.getIntent(text);
        console.log(response["intent"]);
        // console.log(response["entities"]["data:data"][0]["value"]);
        this.lat = null;
        this.long = null;
        this.activeMap = false;

        if (response["intent"]) {
          let intent = response["intent"];
          switch (intent) {
            case "search":
              // let data = response["entities"]["data:data"][0]["value"];
              this.playSoundLocal(processMP3);
              try {
                let responseData = await this.apiStore.getKnowledge(text);
                console.log(responseData);
                this.transcript = responseData["answer"];
                let transcriptVoiceURL = await this.getVoiceTranscript(
                  responseData["answer"]
                );
                console.log(transcriptVoiceURL);
                await this.downloadAndPlay(transcriptVoiceURL["url"]);
              } catch (e) {
                await this.playSoundLocal(problem_chatGPT);
              }

              break;
            case "weather":
              let dataWeather =
                response["entities"]["location:location"][0]["value"];
              this.playSoundLocal(processMP3);
              let responseDataWeather = await this.apiStore.getWeather(
                dataWeather
              );
              console.log(responseDataWeather);
              this.transcript = responseDataWeather["weather"];
              let transcriptVoiceURLWeather = await this.getVoiceTranscript(
                responseDataWeather["weather"]
              );
              console.log(transcriptVoiceURLWeather);
              await this.downloadAndPlay(transcriptVoiceURLWeather["url"]);
              break;
            case "restaurantNearMe":
              let lat = "13.91060";
              let long = "100.67590";
              this.playSoundLocal(processMP3);
              let responseDataRestaurantNearMe =
                await this.apiStore.getRestaurantNearMe(lat, long);
              console.log(responseDataRestaurantNearMe);
              this.transcript = responseDataRestaurantNearMe["restaurant"];
              let transcriptVoiceURLRestaurantNearMe =
                await this.getVoiceTranscript(
                  responseDataRestaurantNearMe["restaurant"]
                );
              console.log(transcriptVoiceURLRestaurantNearMe);
              await this.downloadAndPlay(
                transcriptVoiceURLRestaurantNearMe["url"]
              );
              break;

            case "showMap":
              let place = response["entities"]["location:location"][0]["value"];
              this.playSoundLocal(processMP3);
              let responseDataMap = await this.apiStore.showMap(place);

              if (responseDataMap["lat"] || responseDataMap["long"]) {
                this.transcript = responseDataMap["description"];
                this.lat = responseDataMap["lat"];
                this.long = responseDataMap["long"];
                this.activeMap = true;
                let transcriptVoiceURLMap = await this.getVoiceTranscript(
                  responseDataMap["description"]
                );
                console.log(transcriptVoiceURLMap);
                await this.downloadAndPlay(transcriptVoiceURLMap["url"]);
              }
              break;
            case "IOT":
              // let dataIOT = response["entities"]["data:data"][0]["value"];
              let responseDataIOT = await this.apiStore.getIOT();
              console.log(responseDataIOT);
              this.transcript = responseDataIOT["ans"];
              let transcriptVoiceURLIOT = await this.getVoiceTranscript(
                responseDataIOT["ans"]
              );
              console.log(transcriptVoiceURLIOT);
              await this.downloadAndPlay(transcriptVoiceURLIOT["url"]);
              break;
            case "on_security":
              let responseDataSecurityOn = await this.apiStore.onSecurity();
              console.log(responseDataSecurityOn);
              this.transcript = "เปิดระบบความปลอดภัยเรียบร้อยแล้วครับ";
              this.playSoundLocal(on_security);
              this.transcript = "";
              break;
            case "off_security":
              let responseDataSecurityOff = await this.apiStore.offSecurity();
              console.log(responseDataSecurityOff);
              this.transcript = "ปิดระบบความปลอดภัยเรียบร้อยแล้วครับ";
              this.playSoundLocal(off_security);
              this.transcript = "";
              break;
            default:
              console.err("No intent found!");
          }
        }
      }

      return;
    },
    async getVoiceTranscript(text) {
      let response = await this.apiStore.getVoiceTranscript(text);

      return response;
    },
    async downloadAndPlay(urlDonwoload) {
      const url = urlDonwoload;
      var audio = new Audio(url);

      try {
        await audio.play();

        //   // When audio playback finishes, revoke the URL object
        audio.addEventListener("ended", () => {
          // URL.revokeObjectURL(blobUrl);
          this.transcript = "";
        });
      } catch (error) {
        console.error("Error downloading or playing file:", error);
        this.playSoundLocal(problem_sound);
      }
    },
    async playSoundLocal(path) {
      const audio = new Audio(path);
      audio.play();
    },
  },
};
</script>

<style scoped>
.red {
  background-color: red;
}
</style>
