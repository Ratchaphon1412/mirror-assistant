<script setup>
import { MapboxMap } from "@studiometa/vue-mapbox-gl";
</script>

<template>
  <MapboxMap
    style="height: 400px; width: 400px"
    access-token="pk.eyJ1IjoicmF0Y2hhcGhvbjE0MTIiLCJhIjoiY2xmNnYzMGF0MHE3ODNybzlhdjgwMHZoMyJ9.xZpDt79t_DsJxeiS-IXV2w"
    map-style="mapbox://styles/mapbox/streets-v11"
    :center="[0, 0]"
    :zoom="1"
  />
</template>
