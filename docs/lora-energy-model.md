# LoRa / Radio Energy Model

Radio energy is estimated as:

`E_tx = V x I_tx x t_airtime`

This is an estimate. Real LoRa/LoRaWAN energy depends on spreading factor, bandwidth, coding rate, preamble, payload size, retries, confirmed uplinks, listen windows, hardware module, antenna path, and firmware behavior.


## Payload-size warning

The old fixed 24-byte runtime estimate is now only the documented default fallback. For serious LoRa/LoRaWAN estimates, configure `reportPayloadEstimator()` and provide a radio adapter duration function that accounts for payload length and radio configuration.
