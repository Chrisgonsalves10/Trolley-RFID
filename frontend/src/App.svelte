<script>
  import TailwindCss from "./TailwindCSS.svelte";
  import { onMount } from "svelte";
  import axios from "axios";

  let show = true;
  let selected = "Standard shipping - ₹50.00";
  let shippingOptions = ["Standard shipping - ₹50.00", "Pick Up - ₹0.00"];
  const endpoint = "http://localhost:8000";
  var itemsRes = [];
  var items = [];

  $: incrementQuantity = (n) => {
    items[n].quantity += 1;
  };
  onMount(async function () {
    const response = await axios.get(endpoint);
    // console.log(response.data);
    itemsRes = response.data;
    items = itemsRes.values;
  });

  $: total = items.reduce((sum, item) => sum + item.price * item.quantity, 0);
  $: removeFromCart = (id) => {
    const objWithIdIndex = items.findIndex((obj) => {
      obj.id === id;
    });
    console.log("Removing " + objWithIdIndex);
    items.splice(objWithIdIndex, 1);
    console.log(items);
    items = items;
    return;
  };
</script>

<TailwindCss />

<div class="container mx-auto mt-10">
  <div class="flex shadow-md my-10">
    <div class="w-3/4 bg-white px-10 py-10">
      <div class="flex justify-between border-b pb-8">
        <h1 class="font-semibold text-2xl">Shopping Cart</h1>
        <h2 class="font-semibold text-2xl">{items.length} Items</h2>
      </div>

      {#if items.length == 0}
        <div class="flex items-center my-40">
          <div class="mx-auto">
            <img
              src="https://img.icons8.com/dotty/80/000000/empty-box.png"
              alt="Empty Box"
              class="text-center mx-auto" />
            <h2 class="font-semibold text-4xl text-gray-500">Cart is empty</h2>
          </div>
        </div>
      {:else}
        <div class="flex mt-10 mb-5">
          <h3 class="font-semibold text-gray-600 text-xs uppercase w-2/5">Product Details</h3>
          <h3 class="font-semibold text-center text-gray-600 text-xs uppercase w-1/5 text-center">
            Quantity
          </h3>
          <h3 class="font-semibold text-center text-gray-600 text-xs uppercase w-1/5 text-center">
            Price
          </h3>
          <h3 class="font-semibold text-center text-gray-600 text-xs uppercase w-1/5 text-center">
            Total
          </h3>
        </div>
        {#each items as item}
          <div class="flex items-center hover:bg-gray-100 -mx-8 px-6 py-5">
            <div class="flex w-2/5">
              <div class="w-20">
                <img class="h-24" src={item.imgLink} alt="Foto" />
              </div>
              <div class="flex flex-col justify-center ml-4 flex-grow">
                <span class="font-bold text-lg text-teal-700">{item.itemname}</span>
              </div>
            </div>
            <div class="flex justify-center w-1/5">
              <div on:click={removeFromCart(item.id)}>
                <img
                  class="fill-current text-gray-600 w-8"
                  src="https://i.ibb.co/gR40BH0/icons8-remove-48.png"
                  alt="icons8-remove-48" />
              </div>

              <input class="mx-2 border text-center w-8" type="text" value={item.quantity} />

              <svg
                on:click={incrementQuantity(item.id)}
                class="fill-current text-gray-600 w-3"
                viewBox="0 0 448 512">
                <path
                  d="M416 208H272V64c0-17.67-14.33-32-32-32h-32c-17.67 0-32 14.33-32 32v144H32c-17.67 0-32 14.33-32 32v32c0 17.67 14.33 32 32 32h144v144c0 17.67 14.33 32 32 32h32c17.67 0 32-14.33 32-32V304h144c17.67 0 32-14.33 32-32v-32c0-17.67-14.33-32-32-32z" />
              </svg>
            </div>
            <span class="text-center w-1/5 font-semibold text-sm">₹{item.price}</span>
            <span class="text-center w-1/5 font-semibold text-sm"
              >₹{item.price * item.quantity}</span>
          </div>
        {/each}
      {/if}
      <a href="#ssss" class="flex font-semibold text-indigo-600 text-sm mt-10">
        <svg class="fill-current mr-2 text-indigo-600 w-4" viewBox="0 0 448 512">
          <path
            d="M134.059 296H436c6.627 0 12-5.373 12-12v-56c0-6.627-5.373-12-12-12H134.059v-46.059c0-21.382-25.851-32.09-40.971-16.971L7.029 239.029c-9.373 9.373-9.373 24.569 0 33.941l86.059 86.059c15.119 15.119 40.971 4.411 40.971-16.971V296z" />
        </svg>
        Continue Shopping
      </a>
    </div>

    <div id="summary" class="w-1/4 px-8 py-10">
      <h1 class="font-semibold text-2xl border-b pb-8">Order Summary</h1>
      <div class="flex justify-between mt-10 mb-5">
        <span class="font-semibold text-sm uppercase">Items - {items.length}</span>
        <span class="font-semibold text-sm">₹{total}</span>
      </div>
      <div>
        <p class="font-medium inline-block mb-3 text-sm uppercase">Shipping</p>
        <select class="block p-2 text-gray-600 w-full text-sm" bind:value={selected}>
          {#each shippingOptions as value}<option {value}>{value}</option>{/each}
        </select>
      </div>
      <div class="py-10">
        <label for="promo" class="font-semibold inline-block mb-3 text-sm uppercase"
          >Promo Code</label>
        <input type="text" id="promo" placeholder="Enter your code" class="p-2 text-sm w-full" />
      </div>
      <button class="bg-red-500 hover:bg-red-600 px-5 py-2 text-sm text-white uppercase"
        >Apply</button>
      <div class="border-t mt-8">
        <div class="flex font-semibold justify-between py-6 text-sm uppercase">
          <span>Total cost</span>
          {#if selected === "Standard shipping - ₹50.00"}
            <span>₹{total + 50}</span>
          {:else}
            <span>₹{total}</span>
          {/if}
        </div>
        <button
          class="bg-indigo-500 font-semibold hover:bg-indigo-600 py-3 text-sm text-white uppercase w-full"
          >Checkout</button>
      </div>
    </div>
  </div>
</div>
