<template>
  <NavbarFooter>
    <div class="mx-auto">
      <AstroSpaceBackground />

      <Details />
    </div>
  </NavbarFooter>
</template>
<script>
import NavbarFooter from "@/layouts/NavbarFooter.vue";
import AstroSpaceBackground from "@/components/AstroSpaceBackground.vue";
import Details from "@/components/Details.vue";

export default {
  data() {},
  components: {
    NavbarFooter,
    AstroSpaceBackground,
    Details,
  },
};
</script>

<style scoped>
.red {
  background-color: red;
}
</style>
