<script>
  async function getUsers() {
    let response = await fetch("https://api.jsonbin.io/v3/b/63479f600e6a79321e26bb2b?meta=false");
    let items = await response.json();
    return items;
  }
  const promise = getUsers();
</script>

<div>
  {#await promise}
    <p>Loading...</p>
  {:then items}
    {#each items as item}
      <p>Price is {item.price}, ItemName: {item.itemname}</p>
    {/each}
  {:catch error}
    <p style="color: red">{error.message}</p>
  {/await}
</div>
 */
