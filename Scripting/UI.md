# UI/HUD related functions.

 Functions related to hud/ui time. They have a global scope and can be called by any script in the map.
 
## Scope: Global



  ##### DrawTexture
> void DrawTexture(string texturedict, string texturename, float x, float y, float width, float height, float heading, int r, int g, int b, int alpha);
>
> // Make sure to call this every frame, works with streamed custom textures.

  ##### DrawRectangle
> void DrawRectangle(float x, float y, float widht, float height, int r, int g, int b, int a);
>
> // Make sure to call this every frame.

  ##### DrawSubtitle
> void DrawSubtitle(string txt, float x, float y, float fontsize, int font);
>
> // Make sure to call this every frame.

  ##### CreatePromptInput
> void CreatePromptInput(string input, string text, std::string tag);
>
> // Call only once!, use DoesPromptExist to make sure you dont create the same prompt several times, tag must be uniqe as its the only handle to the prompt you get!

  ##### IsPromptCompleted
> bool IsPromptCompleted(string tag);
>
> // Checks if the prompt has been completed, returns true if so.


  ##### DoesPromptExistbtitle
> bool DoesPromptExist(string tag);
>
> // Checks if the prompt exist returns true if so.

  ##### DeletePrompt
> void DeletePrompt(string tag);
>
> // Deletes the prompt with specified tag.

  ##### GetPromptGroupIdFromEntity
> int GetPromptGroupIdFromEntity(int entity);
>
> // Returns Prompt group id for entity (mainly used with peds).

