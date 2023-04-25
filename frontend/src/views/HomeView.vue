<template>
  <NavbarFooter>
    <div class="mx-auto h-full">
      <AstroSpaceBackground />
      <!-- <DetailFeature />
      <About /> -->
    </div>
  </NavbarFooter>
</template>
<script>
import NavbarFooter from "@/layouts/NavbarFooter.vue";
import AstroSpaceBackground from "@/components/AstroSpaceBackground.vue";
import DetailFeature from "@/components/DetailFeature.vue";
import Details from "@/components/Details.vue";
import About from "@/components/About.vue";
export default {
  data() {},
  components: {
    NavbarFooter,
    AstroSpaceBackground,
    Details,
    DetailFeature,
    About,
  },
};
</script>

<style scoped>
.red {
  background-color: red;
}
</style>
