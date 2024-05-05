var simplemaps_namap_mapdata={
  main_settings: {
   //General settings
    width: "600", //'700' or 'responsive'
    background_color: "#FFFFFF",
    background_transparent: "yes",
    border_color: "#ffffff",
    popups: "detect",
    
    //State defaults
    state_description: "State description",
    state_color: "#D7A659",
    state_hover_color: "#B50409",
    state_url: "",
    border_size: 1.5,
    all_states_inactive: "no",
    all_states_zoomable: "no",
    
    //Location defaults
    location_description: "Location description",
    location_color: "#FF0067",
    location_opacity: 0.8,
    location_hover_opacity: 1,
    location_url: "",
    location_size: 25,
    location_type: "square",
    location_image_source: "frog.png",
    location_border_color: "#FFFFFF",
    location_border: 2,
    location_hover_border: 2.5,
    all_locations_inactive: "no",
    all_locations_hidden: "no",
    
    //Label defaults
    label_color: "#ffffff",
    label_hover_color: "#ffffff",
    label_size: 14,
    label_font: "Arial",
    hide_labels: "no",
    manual_zoom: "no",
    back_image: "no",
    arrow_color: "#cecece",
    arrow_color_border: "#808080",
    initial_back: "no",
    initial_zoom: -1,
    initial_zoom_solo: "no",
    region_opacity: 1,
    region_hover_opacity: 0.6,
    zoom_out_incrementally: "yes",
    zoom_percentage: 0.99,
    zoom_time: 0.5,
    
    //Popup settings
    popup_color: "white",
    popup_opacity: 0.9,
    popup_shadow: 1,
    popup_corners: 5,
    popup_font: "12px/1.5 Verdana, Arial, Helvetica, sans-serif",
    popup_nocss: "no",
    
    //Advanced settings
    div: "map",
    keyboard_navigation: "yes",
    auto_load: "yes",
    url_new_tab: "no",
    images_directory: "default",
    fade_time: 0.1,
    import_labels: "no",
    link_text: "View Website",
    state_image_url: "",
    state_image_position: "",
    location_image_url: ""
  },
  state_specific: {
    AB: {
      name: "Alberta"
    },
    AK: {
      name: "Alaska"
    },
    AL: {
      name: "Alabama"
    },
    AR: {
      name: "Arkansas"
    },
    AZ: {
      name: "Arizona"
    },
    BC: {
      name: "British Columbia"
    },
    CA: {
      name: "California"
    },
    CO: {
      name: "Colorado"
    },
    CT: {
      name: "Connecticut"
    },
    DC: {
      name: "District of Columbia"
    },
    DE: {
      name: "Delaware"
    },
    FL: {
      name: "Florida"
    },
    GA: {
      name: "Georgia"
    },
    HI: {
      name: "Hawaii"
    },
    IA: {
      name: "Iowa"
    },
    ID: {
      name: "Idaho"
    },
    IL: {
      name: "Illinois"
    },
    IN: {
      name: "Indiana"
    },
    KS: {
      name: "Kansas"
    },
    KY: {
      name: "Kentucky"
    },
    LA: {
      name: "Louisiana"
    },
    MA: {
      name: "Massachusetts"
    },
    MB: {
      name: "Manitoba"
    },
    MD: {
      name: "Maryland"
    },
    ME: {
      name: "Maine"
    },
    MI: {
      name: "Michigan"
    },
    MN: {
      name: "Minnesota"
    },
    MO: {
      name: "Missouri"
    },
    MS: {
      name: "Mississippi"
    },
    MT: {
      name: "Montana"
    },
    NB: {
      name: "New Brunswick"
    },
    NC: {
      name: "North Carolina"
    },
    ND: {
      name: "North Dakota"
    },
    NE: {
      name: "Nebraska"
    },
    NH: {
      name: "New Hampshire"
    },
    NJ: {
      name: "New Jersey"
    },
    NL: {
      name: "Newfoundland and Labrador"
    },
    NM: {
      name: "New Mexico"
    },
    NS: {
      name: "Nova Scotia"
    },
    NT: {
      name: "Northwest Territories"
    },
    NU: {
      name: "Nunavut"
    },
    NV: {
      name: "Nevada"
    },
    NY: {
      name: "New York"
    },
    OH: {
      name: "Ohio"
    },
    OK: {
      name: "Oklahoma"
    },
    ON: {
      name: "Ontario"
    },
    OR: {
      name: "Oregon"
    },
    PA: {
      name: "Pennsylvania"
    },
    PE: {
      name: "Prince Edward Island"
    },
    QC: {
      name: "Québec"
    },
    RI: {
      name: "Rhode Island"
    },
    SC: {
      name: "South Carolina"
    },
    SD: {
      name: "South Dakota"
    },
    SK: {
      name: "Saskatchewan"
    },
    TN: {
      name: "Tennessee"
    },
    TX: {
      name: "Texas"
    },
    UT: {
      name: "Utah"
    },
    VA: {
      name: "Virginia"
    },
    VT: {
      name: "Vermont"
    },
    WA: {
      name: "Washington"
    },
    WI: {
      name: "Wisconsin"
    },
    WV: {
      name: "West Virginia"
    },
    WY: {
      name: "Wyoming"
    },
    MX: {
      name: "Mexico",
      hide: "yes"
    },
    YT: {
      name: "Yukon"
    }
  },
  locations: {},
  labels: {
    NH: {
      parent_id: "NH",
      display: "all",
      pill: "yes",
      width: 30,
      x: 920,
      y: 565
    },
    MA: {
      parent_id: "MA",
      display: "all",
      pill: "yes",
      width: 30,
      x: 920,
      y: 590
    },
    CT: {
      parent_id: "CT",
      display: "all",
      pill: "yes",
      width: 30,
      x: 920,
      y: 615
    },
    RI: {
      parent_id: "RI",
      display: "all",
      pill: "yes",
      width: 30,
      x: 920,
      y: 640
    },
    MD: {
      parent_id: "MD",
      display: "all",
      pill: "yes",
      width: 30,
      x: 920,
      y: 665
    },
    VT: {
      parent_id: "VT",
      display: "all",
      pill: "yes",
      width: 30,
      x: 885,
      y: 590
    },
    NJ: {
      parent_id: "NJ",
      display: "all",
      pill: "yes",
      width: 30,
      x: 885,
      y: 615
    },
    DE: {
      parent_id: "DE",
      display: "all",
      pill: "yes",
      width: 30,
      x: 885,
      y: 640
    },
    DC: {
      parent_id: "DC",
      display: "all",
      pill: "yes",
      width: 30,
      x: 885,
      y: 665
    },
    HI: {
      parent_id: "HI",
      display: "all",
      pill: "yes",
      width: 30,
      x: 290,
      y: 640
    },
    WV: {
      parent_id: "WV",
      x: "803.4",
      y: "601.7",
      size: 11
    },
    TX: {
      parent_id: "TX",
      x: 630,
      y: 695
    },
    AK: {
      parent_id: "AK",
      x: 375,
      y: 201
    },
    PE: {
      parent_id: "PE",
      display: "all",
      pill: "yes",
      width: 30,
      x: 965,
      y: 490
    },
    NS: {
      parent_id: "NS",
      display: "all",
      pill: "yes",
      width: 30,
      x: 965,
      y: 515
    },
    MX: {
      parent_id: "MX",
      x: "601.3",
      y: "788.5",
      name: "Mexico"
    },
    MB: {
      parent_id: "MB",
      x: "656.4",
      y: "417.8"
    },
    SK: {
      parent_id: "SK",
      x: "595.6",
      y: "425.6"
    },
    AB: {
      parent_id: "AB",
      x: "534.6",
      y: "407"
    },
    BC: {
      parent_id: "BC",
      x: "470.8",
      y: "383.5"
    },
    NU: {
      parent_id: "NU",
      x: "652",
      y: "289.5"
    },
    NT: {
      parent_id: "NT",
      x: "528.4",
      y: "293.2"
    },
    YT: {
      parent_id: "YT",
      x: "438.5",
      y: "275.6"
    },
    ON: {
      parent_id: "ON",
      x: "729.8",
      y: "452.6"
    },
    QC: {
      parent_id: "QC",
      x: "833.9",
      y: "431.3"
    },
    NB: {
      parent_id: "NB",
      x: "900.6",
      y: "483.3"
    },
    NL: {
      parent_id: "NL",
      x: "901.1",
      y: "384.5"
    },
    MN: {
      parent_id: "MN",
      x: "677.5",
      y: "520.6"
    },
    MT: {
      parent_id: "MT",
      x: "557.2",
      y: "507.5"
    },
    ND: {
      parent_id: "ND",
      x: "630.3",
      y: "509.3"
    },
    ID: {
      parent_id: "ID",
      x: "509.2",
      y: "540.2"
    },
    WA: {
      parent_id: "WA",
      x: "476.8",
      y: "485"
    },
    AZ: {
      parent_id: "AZ",
      x: "516.2",
      y: "650.8"
    },
    CA: {
      parent_id: "CA",
      x: "447.7",
      y: "608.3"
    },
    CO: {
      parent_id: "CO",
      x: "579.7",
      y: "604.6"
    },
    NV: {
      parent_id: "NV",
      x: "481.5",
      y: "582.4"
    },
    NM: {
      parent_id: "NM",
      x: "569.4",
      y: "656.2"
    },
    OR: {
      parent_id: "OR",
      x: "462",
      y: "524.9"
    },
    UT: {
      parent_id: "UT",
      x: "526.1",
      y: "595.7"
    },
    WY: {
      parent_id: "WY",
      x: "567.6",
      y: "556.2"
    },
    AR: {
      parent_id: "AR",
      x: "699.3",
      y: "655.2"
    },
    IA: {
      parent_id: "IA",
      x: "687.5",
      y: "573.4"
    },
    KS: {
      parent_id: "KS",
      x: "644.2",
      y: "614.6"
    },
    MO: {
      parent_id: "MO",
      x: "697.5",
      y: "617.3"
    },
    NE: {
      parent_id: "NE",
      x: "632.8",
      y: "579.3"
    },
    OK: {
      parent_id: "OK",
      x: "656.4",
      y: "650.3"
    },
    SD: {
      parent_id: "SD",
      x: "630.6",
      y: "544.5"
    },
    LA: {
      parent_id: "LA",
      x: "699.3",
      y: "691"
    },
    AL: {
      parent_id: "AL",
      x: "756.2",
      y: "677.6"
    },
    FL: {
      parent_id: "FL",
      x: "813.1",
      y: "719.2"
    },
    GA: {
      parent_id: "GA",
      x: "790.9",
      y: "675.4"
    },
    MS: {
      parent_id: "MS",
      x: "727.7",
      y: "679.7"
    },
    SC: {
      parent_id: "SC",
      x: "813.1",
      y: "657"
    },
    IL: {
      parent_id: "IL",
      x: "724.8",
      y: "593"
    },
    IN: {
      parent_id: "IN",
      x: "753.5",
      y: "594.2"
    },
    KY: {
      parent_id: "KY",
      x: "772.2",
      y: "617"
    },
    NC: {
      parent_id: "NC",
      x: "831.6",
      y: "634.4"
    },
    OH: {
      parent_id: "OH",
      x: "781",
      y: "587.7"
    },
    TN: {
      parent_id: "TN",
      x: "756.7",
      y: "641.3"
    },
    VA: {
      parent_id: "VA",
      x: "822.2",
      y: "611.8"
    },
    WI: {
      parent_id: "WI",
      x: "715.9",
      y: "539.3"
    },
    NY: {
      parent_id: "NY",
      x: "844.7",
      y: "541.3"
    },
    PA: {
      parent_id: "PA",
      x: "824.8",
      y: "571.4"
    },
    ME: {
      parent_id: "ME",
      x: "882.7",
      y: "502.6"
    },
    MI: {
      parent_id: "MI",
      x: "760.2",
      y: "556.5"
    }
  },
  legend: {
    entries: []
  },
  regions: {
    "0": {
      states: [
        "HI",
        "AK",
        "FL",
        "NH",
        "VT",
        "ME",
        "RI",
        "NY",
        "PA",
        "NJ",
        "DE",
        "MD",
        "VA",
        "WV",
        "OH",
        "IN",
        "IL",
        "CT",
        "WI",
        "NC",
        "DC",
        "MA",
        "TN",
        "AR",
        "MO",
        "GA",
        "SC",
        "KY",
        "AL",
        "LA",
        "MS",
        "IA",
        "MN",
        "OK",
        "TX",
        "NM",
        "KS",
        "NE",
        "SD",
        "ND",
        "WY",
        "MT",
        "CO",
        "UT",
        "AZ",
        "NV",
        "OR",
        "WA",
        "CA",
        "MI",
        "ID",
        "GU",
        "VI",
        "PR",
        "MP",
        "AS",
        "MX"
      ],
      name: "United States of America",
      zoomable: "yes"
    },
    "1": {
      states: [
        "AB",
        "BC",
        "SK",
        "MB",
        "ON",
        "QC",
        "NB",
        "PE",
        "NS",
        "NL",
        "NU",
        "NT",
        "YT"
      ],
      name: "Canada",
      zoomable: "yes"
    }
  }
};