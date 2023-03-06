<template>
  <kinesis-container
    class="relative h-screen overflow-y-hidden overflow-x-hidden"
    event="scroll"
  >
    <kinesis-element :strength="20" type="depth">
      <img
        class="h-auto w-full object-cover sm:h-screen absolute"
        src="@/assets/images/space-background.svg"
        alt="image description"
      />

      <kinesis-element :strength="50" type="depth_inv" axis="y">
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
