<template>
  <section>
    <kinesis-container
      class="relative h-screen overflow-y-hidden overflow-x-hidden"
      event="scroll"
    >
      <kinesis-element :strength="100" type="translate">
        <img
          class="h-auto w-full object-cover sm:h-screen absolute"
          src="@/assets/images/space-background.svg"
          alt="image description"
        />
        <!--text-->
        <kinesis-element :strength="600" type="translate" axis="y">
          <div
            class="absolute inset-0.5 flex flex-col items-center justify-center h-screen"
          >
            <div
              class="text-center lg:w-1/5 md:w-2/5 ms:w-3/5 xs:w-4/5 dark:text-gray-100 text-gray-900"
            >
              <h1
                class="lg:text-5xl md:text-2xl xs:text-xl font-bold subpixel-antialiased whitespace-pre-line"
              >
                Welcome <br />
                to the Space
              </h1>
              <p
                class="font-medium text-base subpixel-antialiased text-center indent-2"
              >
                
              </p>
            </div>
          </div>
        </kinesis-element>
        <!--rocket-->
        <kinesis-element :strength="120" type="translate" axis="y">
          <img
            class="h-auto w-full object-cover sm:h-screen absolute"
            src="@/assets/images/space-rocket.svg"
            alt="image description"
          />
        </kinesis-element>
        <!--astro-->
        <kinesis-element :strength="0" type="depth">
          <img
            class="h-auto w-full object-cover sm:h-screen absolute"
            src="@/assets/images/space-astro-rounded.svg"
            alt="image description"
          />
        </kinesis-element>
      </kinesis-element>
    </kinesis-container>
  </section>
</template>

<script>
import { KinesisContainer, KinesisElement } from "vue-kinesis";
export default {
  components: {
    KinesisContainer,
    KinesisElement,
  },
};
</script>

<style scoped>
.red {
  background-color: red;
}
</style>
