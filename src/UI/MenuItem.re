open Revery;
open Revery.UI;
open Oni_Core;
open Oni_Model;

module FontAwesome = Oni_Components.FontAwesome;
module FontIcon = Oni_Components.FontIcon;

module Constants = {
  let iconSize = 20.;
};

module Styles = {
  let bg = (~theme: Theme.t, ~isFocused) =>
    isFocused ? theme.listFocusBackground : theme.menuBackground;

  let text = (~theme: Theme.t, ~font: UiFont.t, ~isFocused) =>
    Style.[
      fontFamily(font.fontFile),
      fontSize(font.fontSize),
      color(theme.menuForeground),
      backgroundColor(bg(~theme, ~isFocused)),
    ];

  let container = (~theme, ~isFocused) =>
    Style.[
      padding(10),
      flexDirection(`Row),
      backgroundColor(bg(~theme, ~isFocused)),
    ];

  let icon = fg =>
    Style.[
      fontFamily("seti.ttf"),
      fontSize(Constants.iconSize),
      color(fg),
      width(int_of_float(Constants.iconSize *. 0.75)),
      height(int_of_float(Constants.iconSize *. 0.85)),
      textWrap(TextWrapping.NoWrap),
      marginRight(10),
    ];

  let label = (~font: UiFont.t, ~theme: Theme.t, ~isFocused, ~custom) =>
    Style.(
      merge(
        ~source=
          Style.[
            fontFamily(font.fontFile),
            textOverflow(`Ellipsis),
            fontSize(12.),
            color(theme.menuForeground),
            backgroundColor(bg(~theme, ~isFocused)),
          ],
        ~target=custom,
      )
    );

  let clickable = Style.[cursor(Revery.MouseCursors.pointer)];
};

let noop = () => ();

let make =
    (
      ~style=[],
      ~icon=None,
      ~label,
      ~isFocused,
      ~theme,
      ~onClick=noop,
      ~onMouseOver=noop,
      (),
    ) => {
  let state = GlobalContext.current().state;
  let font = State.(state.uiFont);

  let iconView =
    switch (icon) {
    | Some(v) =>
      IconTheme.IconDefinition.(
        <Text
          style={Styles.icon(v.fontColor)}
          text={FontIcon.codeToIcon(v.fontCharacter)}
        />
      )

    | None => <Text style={Styles.icon(Colors.transparentWhite)} text="" />
    };

  let labelView =
    switch (label) {
    | `Text(text) =>
      let style = Styles.label(~font, ~theme, ~isFocused, ~custom=style);
      <Text style text />;
    | `Custom(view) => view
    };

  <Sneakable style=Styles.clickable onClick>
    <View
      onMouseOver={_ => onMouseOver()}
      style={Styles.container(~theme, ~isFocused)}>
      iconView
      labelView
    </View>
  </Sneakable>;
};
