<template>
  <section class="dark:bg-gray-900 bg-gray-100">
    <Navbar />
    <div class="mx-auto w-full h-full">
      <slot />
    </div>
    <Footer />
  </section>
</template>
<script>
import Navbar from "@/components/Navbar.vue";
import Footer from "@/components/Footer.vue";

export default {
  name: "NavbarFooter",
  data() {},
  components: {
    Navbar,
    Footer,
  },
};
</script>

<style scoped>
.red {
  background-color: red;
}
</style>
