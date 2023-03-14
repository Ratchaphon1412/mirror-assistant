<script setup>
// import { MapboxMap } from "@studiometa/vue-mapbox-gl";

import { Loader } from "@googlemaps/js-api-loader";
import * as THREE from "three";
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader.js";
import { ref, onMounted, defineProps } from "vue";

const props = defineProps({
  lat: {
    type: Number,
    default: 48.8584,
  },
  long: {
    type: Number,
    default: 2.2945,
  },
});

const latProp = ref(props.lat);
const longProp = ref(props.long);

const apiOptions = {
  apiKey: "AIzaSyDVDXo_WL6ZnT36gKd0bC2_er_gEcyXjhc",
  version: "beta",
  map_ids: ["209e468b6fc515fd"],
};

// const mapDiv = ref(null);
const webglOverlayView = new google.maps.WebGLOverlayView();
let scene, renderer, camera, loader;
camera = new THREE.PerspectiveCamera();
scene = new THREE.Scene();
loader = new GLTFLoader();
const mapOptions = {
  tilt: 0,
  heading: 0,
  zoom: 18,
  center: { lat: latProp.value, lng: longProp.value },
  mapId: "209e468b6fc515fd",
  styles: [
    { elementType: "geometry", stylers: [{ color: "#242f3e" }] },
    { elementType: "labels.text.stroke", stylers: [{ color: "#242f3e" }] },
    { elementType: "labels.text.fill", stylers: [{ color: "#746855" }] },
    {
      featureType: "administrative.locality",
      elementType: "labels.text.fill",
      stylers: [{ color: "#d59563" }],
    },
    {
      featureType: "poi",
      elementType: "labels.text.fill",
      stylers: [{ color: "#d59563" }],
    },
    {
      featureType: "poi.park",
      elementType: "geometry",
      stylers: [{ color: "#263c3f" }],
    },
    {
      featureType: "poi.park",
      elementType: "labels.text.fill",
      stylers: [{ color: "#6b9a76" }],
    },
    {
      featureType: "road",
      elementType: "geometry",
      stylers: [{ color: "#38414e" }],
    },
    {
      featureType: "road",
      elementType: "geometry.stroke",
      stylers: [{ color: "#212a37" }],
    },
    {
      featureType: "road",
      elementType: "labels.text.fill",
      stylers: [{ color: "#9ca5b3" }],
    },
    {
      featureType: "road.highway",
      elementType: "geometry",
      stylers: [{ color: "#746855" }],
    },
    {
      featureType: "road.highway",
      elementType: "geometry.stroke",
      stylers: [{ color: "#1f2835" }],
    },
    {
      featureType: "road.highway",
      elementType: "labels.text.fill",
      stylers: [{ color: "#f3d19c" }],
    },
    {
      featureType: "transit",
      elementType: "geometry",
      stylers: [{ color: "#2f3948" }],
    },
    {
      featureType: "transit.station",
      elementType: "labels.text.fill",
      stylers: [{ color: "#d59563" }],
    },
    {
      featureType: "water",
      elementType: "geometry",
      stylers: [{ color: "#17263c" }],
    },
    {
      featureType: "water",
      elementType: "labels.text.fill",
      stylers: [{ color: "#515c6d" }],
    },
    {
      featureType: "water",
      elementType: "labels.text.stroke",
      stylers: [{ color: "#17263c" }],
    },
  ],
};

async function initMap() {
  const apiLoader = new Loader(apiOptions);

  // const mapDivEl = mapDiv.value;
  const mapDivEl = document.getElementById("mapDiv");

  await apiLoader.load();
  return new google.maps.Map(mapDivEl, mapOptions);
}

async function initWebglOverlayView(map) {
  webglOverlayView.onAdd = () => {
    const ambientLight = new THREE.AmbientLight(0x000000, 0.75); // soft white light
    scene.add(ambientLight);
    const directionalLight = new THREE.DirectionalLight(0x000000, 0.25);
    directionalLight.position.set(0.5, -1, 0.5);
    scene.add(directionalLight);

    // const source = "pin.gltf";
    loader.load("/assets/models/pin.gltf", (gltf) => {
      gltf.scene.scale.set(25, 25, 25);
      gltf.scene.rotation.x = (180 * Math.PI) / 180;
      scene.add(gltf.scene);
    });
  };

  webglOverlayView.onContextRestored = (gl) => {
    renderer = new THREE.WebGLRenderer({
      canvas: gl.gl.canvas,
      context: gl.gl,
      ...gl.gl.getContextAttributes(),
      //   alpha: gl.getContextAttributes().alpha,
      //   depth: gl.getContextAttributes().depth,
      //   stencil: gl.getContextAttributes().stencil,
      //   antialias: gl.getContextAttributes().antialias,
      //   premultipliedAlpha: gl.getContextAttributes().premultipliedAlpha,
      //   preserveDrawingBuffer: gl.getContextAttributes().preserveDrawingBuffer,
      //   failIfMajorPerformanceCaveat:
      //     gl.getContextAttributes().failIfMajorPerformanceCaveat,
      //   powerPreference: gl.getContextAttributes().powerPreference,
    });

    renderer.autoClear = false;

    loader.manager.onLoad = () => {
      renderer.setAnimationLoop(() => {
        map.moveCamera({
          tilt: mapOptions.tilt,
          heading: mapOptions.heading,
          zoom: mapOptions.zoom,
        });

        if (mapOptions.tilt < 67.5) {
          mapOptions.tilt += 0.5;
        } else if (mapOptions.heading <= 360) {
          mapOptions.heading += 0.2;
        } else {
          renderer.setAnimationLoop(null);
        }
      });
    };
  };
  webglOverlayView.onDraw = (gl, transformer) => {
    // const matrix = gl.transformer.fromLatLngAltitude(
    //   mapOptions.center.lat,
    //   mapOptions.center.lng,
    //   120
    // );

    // camera.projectionMatrix = new THREE.Matrix4().fromArray(matrix);

    webglOverlayView.requestRedraw();
    renderer.render(scene, camera);
    renderer.resetState();
  };
  webglOverlayView.setMap(map);
}

onMounted(() => {
  (async () => {
    const map = await initMap();
    // await initMap();

    // const map = new google.maps.Map(mapDiv.value, mapOptions);
    await initWebglOverlayView(map);
  })();

  return {
    mapDiv,
  };
});
</script>

<template>
  <div ref="mapDiv" id="mapDiv" class="h-[800px] w-[1000px]"></div>

  <!-- <MapboxMap
    style="height: 400px; width: 400px"
    access-token="pk.eyJ1IjoicmF0Y2hhcGhvbjE0MTIiLCJhIjoiY2xmNnYzMGF0MHE3ODNybzlhdjgwMHZoMyJ9.xZpDt79t_DsJxeiS-IXV2w"
    map-style="mapbox://styles/mapbox/streets-v11"
    :center="[0, 0]"
    :zoom="1"
  /> -->
</template>

<style scoped>
.red {
  background-color: red;
}
</style>
