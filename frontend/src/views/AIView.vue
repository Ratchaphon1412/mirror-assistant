<template>
  <div class="h-screen text-gray-100 bg-black flex justify-center items-center">
    <div class="">
      <div class="flex justify-center">
        <img src="@/assets/images/giphy.gif" class="object-fill h-20 w-20" />
      </div>

      <!-- <div class="h-[800px] bg-gray-300 mb-5">
        <iframe
          width="100%"
          height="100%"
          frameborder="0"
          marginheight="0"
          marginwidth="0"
          title="map"
          scrolling="no"
          src="https://maps.google.com/maps?width=100%&height=600&hl=en&q=%C4%B0zmir+(My%20Business%20Name)&ie=UTF8&t=&z=14&iwloc=B&output=embed"
          style=""
        ></iframe>
      </div> -->

      <!-- <button @click="toggleSpeechRecognition">
        {{ isRecognitionActive ? "Stop" : "Start" }}
      </button> -->
      <!-- <GoogleMap /> -->
      <!-- <p class="text-center self-center">
        {{ transcript }}
        Lorem ipsum dolor sit, amet consectetur adipisicing elit. Sit molestiae
        sapiente nesciunt natus expedita, libero minima dolore porro commodi
        doloremque tempora eaque esse? Harum, repellat. Vero ipsa exercitationem
        voluptatibus consequatur? Lorem ipsum dolor sit, amet consectetur
        adipisicing elit. Consequatur animi doloremque vero incidunt? Placeat
        illo adipisci delectus esse mollitia beatae dicta nihil ipsum nostrum
        nesciunt? Eligendi deleniti numquam exercitationem saepe?
      </p> -->

      <div class="grid grid-cols-6 gap-4">
        <div></div>
        <div class="col-span-4 text-center self-center">
          {{ transcript }}
          <div class="">
            <!-- <GoogleMap /> -->
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
export default {
  setup() {},
  data() {
    return {
      transcript: "",
      recognition: null,
      apiStore: useApiStore(),
      audio: null,
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
      if (finalTranscript.startsWith("บอส")) {
        this.transcript = finalTranscript;
        let text = finalTranscript.replace("บอส", "");
        console.log(text);
        let response = await this.apiStore.getIntent(text);
        console.log(response["intent"]);
        // console.log(response["entities"]["data:data"][0]["value"]);
        if (response["intent"]) {
          let intent = response["intent"];
          switch (intent) {
            case "search":
              // let data = response["entities"]["data:data"][0]["value"];
              let responseData = await this.apiStore.getKnowledge(text);
              console.log(responseData);
              this.transcript = responseData["answer"];
              let transcriptVoiceURL = await this.getVoiceTranscript(
                responseData["answer"]
              );
              console.log(transcriptVoiceURL);
              await this.downloadAndPlay(transcriptVoiceURL["url"]);

              break;
            case "weather":
              let dataWeather =
                response["entities"]["location:location"][0]["value"];
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
      audio.play();
      // try {
      //   // Download file from URL
      //   const response = await fetch(url);
      //   const arrayBuffer = await response.arrayBuffer();

      //   // Create blob object from file data
      //   const blob = new Blob([arrayBuffer], { type: "audio/mpeg" });

      //   // Create URL object from blob and set as audio source
      //   const blobUrl = URL.createObjectURL(blob);
      //   const audio = new Audio(blobUrl);
      //   audio.autoplay = true;
      //   audio.muted = true;
      //   // this.audio = audio;
      //   await audio.play();

      //   // When audio playback finishes, revoke the URL object
      audio.addEventListener("ended", () => {
        // URL.revokeObjectURL(blobUrl);
        this.transcript = "";
      });
      // } catch (error) {
      //   console.error("Error downloading or playing file:", error);
      // }
    },
  },
};
</script>

<style scoped>
.red {
  background-color: red;
}
</style>
