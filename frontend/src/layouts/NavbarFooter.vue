<template>
  <section>
    <Navbar />

    <div class="container mx-auto">
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
