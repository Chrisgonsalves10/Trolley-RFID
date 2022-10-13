<script>
  import TailwindCss from "./TailwindCSS.svelte";
  import { onMount } from "svelte";
  import axios from "axios";

  const endpoint = "http://localhost:8000";
  var itemsRes = [];
  var myLen = 0;
  var items = [];

  onMount(async function () {
    const response = await axios.get(endpoint);
    console.log(response.data);
    itemsRes = response.data;
    myLen = response.data.totalValues;
    items = itemsRes.values;
  });
</script>

<TailwindCss />
<div>
  {#if myLen === 0}
    Cart Empty
  {:else}
    {#each items as item}
      <p>Price is {item.price}, ItemName: {item.itemname}</p>
    {/each}
  {/if}
</div>
