<template>
  <section>
    <kinesis-container
      class="relative h-screen overflow-y-hidden overflow-x-hidden"
      event="scroll"
    >
      <kinesis-element :strength="10" type="translate">
        <img
          class="h-auto w-full object-cover sm:h-screen absolute blur-[2px]"
          src="@/assets/images/space-background.svg"
          alt="image description"
        />
        <kinesis-element :strength="600" type="translate">
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
                Lorem ipsum dolor sit amet consectetur adipisicing elit. Dolore
                numquam voluptatem necessitatibus odit ipsam odio cupiditate, ex
                architecto modi, fugiat blanditiis cumque! Ex reprehenderit
                dicta eveniet veniam aliquid officia tenetur?
              </p>
            </div>
          </div>
        </kinesis-element>

        <kinesis-element :strength="120" type="translate" axis="y">
          <img
            class="h-auto w-full object-cover sm:h-screen absolute"
            src="@/assets/images/space-rocket.svg"
            alt="image description"
          />
        </kinesis-element>
        <kinesis-element :strength="50" type="depth" axis="y">
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
