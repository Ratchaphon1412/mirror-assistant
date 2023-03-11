<template>
  <div class="h-screen text-gray-100 bg-black flex justify-center items-center">
    <div class="">
      <div class="h-[800px] bg-gray-300 mb-5 hidden">
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
      </div>
      <p class="text-center self-center">
        {{ transcript }}
      </p>
    </div>
    <!-- <button @click="startListening">Start Listening</button> -->
  </div>
</template>

<script>
import NavbarFooter from "@/layouts/NavbarFooter.vue";

export default {
  setup() {},
  data() {
    return {
      transcript: "",
    };
  },
  mounted() {
    this.startListening();
  },
  components: {
    NavbarFooter,
  },
  methods: {
    startListening() {
      const recognition = new webkitSpeechRecognition();
      const thaiLang = recognition.lang.search("th-") >= 0 ? "th-TH" : "th-TH";
      recognition.lang = thaiLang;
      recognition.continuous = true;
      recognition.interimResults = true;
      recognition.onresult = (event) => {
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

        let transcriptResult = finalTranscript || interimTranscript;

        // this.transcript = interimTranscript;

        if (transcriptResult.startsWith("บอส")) {
          // console.log(this.transcript);

          this.doSomething(transcriptResult);
        }
      };
      recognition.onend = () => {
        recognition.start();
      };
      recognition.start();
    },
    doSomething(finalTranscript) {
      this.transcript = finalTranscript;
      console.log(finalTranscript);
      return;
    },
  },
};
</script>

<style scoped>
.red {
  background-color: red;
}
</style>
