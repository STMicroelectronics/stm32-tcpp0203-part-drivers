
/**
 * Extract the peripheral instance name from a dot-separated string
 * For example: "adc12.adc1" -> "adc1"
 *
 * @param {string} full_name Full peripheral path (e.g. "adc12.adc1")
 * @returns {string} Instance name (e.g. "adc1"), or empty string on error
 */
function helper_get_instance_name(full_name) {
  try {
    console.info(
      `helper_get_instance_name: full_name=${JSON.stringify(full_name)}`
    );

    if (typeof full_name !== "string" || full_name.length === 0) {
      return "";
    }

    const parts = full_name.split(".");
    const instance_name = parts[parts.length - 1];

    return instance_name || "";
  } catch (e) {
    console.error(`helper_get_instance_name: ${e}`);
    return "";
  }
}

module.exports = {
  helper_get_instance_name
}
